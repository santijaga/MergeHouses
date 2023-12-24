// Fill out your copyright notice in the Description page of Project Settings.

#include "MergeTownPlayerController.h"
#include "MergeHousesGameModeBase.h"
#include "Camera/CameraActor.h"
#include "MainWidgetBase.h"
#include "GameOverWidgetBase.h"
#include "MainMenuWidgetBase.h"
#include "MergeHousesSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "HowToPlayWidget.h"
#include "InformationUserWidgetBase.h"
#include "Sound/SoundCue.h"
#include "Components/AudioComponent.h"
#include "NotificationWidget.h"

void AMergeTownPlayerController::PrintScoresToScreen()
{
	FString ScoresString = FString::Printf(TEXT("Scores: %d"), PlayerScore);

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::White, ScoresString);
	}
}

void AMergeTownPlayerController::SaveHighScore()
{
	UMergeHousesSaveGame* SaveGameInstance = Cast<UMergeHousesSaveGame>(UGameplayStatics::CreateSaveGameObject(UMergeHousesSaveGame::StaticClass()));

	SaveGameInstance->SavedHighScore = PlayerScore;

	UGameplayStatics::SaveGameToSlot(SaveGameInstance, "HighScoreSaveSlot", 0);
}

void AMergeTownPlayerController::LoadHighScore()
{
	UMergeHousesSaveGame* LoadGameInstance = Cast<UMergeHousesSaveGame>(UGameplayStatics::LoadGameFromSlot("HighScoreSaveSlot", 0));

	if (LoadGameInstance)
	{
		HighScore = LoadGameInstance->SavedHighScore;
	}
}

AMergeTownPlayerController::AMergeTownPlayerController()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;

	BGMAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("BGMComponent"));
	GameOverAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("GameOverAudioComponent"));

	TutorialText.Add("Swipe any direction to move all houses same direction");
	TutorialText.Add("Moving two same houses at same place will merge them into new house");
	TutorialText.Add("Try to reach the most advance house");

	TutorialSteps = TutorialText.Num() - 1;
}

void AMergeTownPlayerController::BeginPlay()
{
	Super::BeginPlay();

	LoadSoundSetting();
	LoadTutorialState();
	SetInputMode(FInputModeGameAndUI());
	SetViewTarget(Cast<AMergeHousesGameModeBase>(GetWorld()->GetAuthGameMode())->GetMenuCameraReference());
	SetupBGM();
	SetupGameOverMusic();
	ShowMainMenuUI();
	PlayBGM();
}

void AMergeTownPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (ScoreWidget)
	{
		ScoreWidget->UpdateScores(PlayerScore);
	}
}

void AMergeTownPlayerController::SetMenuCameraActive()
{
	SetViewTargetWithBlend(Cast<AMergeHousesGameModeBase>(GetWorld()->GetAuthGameMode())->GetMenuCameraReference(), CameraBlendSpeed);
}

void AMergeTownPlayerController::SetBoardCameraActive()
{
	SetViewTargetWithBlend(Cast<AMergeHousesGameModeBase>(GetWorld()->GetAuthGameMode())->GetBoardCameraReference(), CameraBlendSpeed);
}

int32 AMergeTownPlayerController::GetScore()
{
	return PlayerScore;
}

void AMergeTownPlayerController::AddScores(int32 PointsToAdd)
{
	PlayerScore += PointsToAdd;
}

void AMergeTownPlayerController::SetScores(int32 PointsToSet)
{
	PlayerScore = PointsToSet;
}

void AMergeTownPlayerController::ResetScores()
{
	PlayerScore = 0;
}

void AMergeTownPlayerController::StoreScores(int32 ScoresToStore)
{
	if (ScoresToStore) {
		StoredScores = ScoresToStore;
	}
	else
	{
		StoredScores = PlayerScore;
	}
}

void AMergeTownPlayerController::RestoreScores()
{
	SetScores(StoredScores);
}

void AMergeTownPlayerController::ShowGameplayUI()
{
	if (ScoreWidgetClass)
	{
		ScoreWidget = CreateWidget<UMainWidgetBase>(this, ScoreWidgetClass);
	}

	if (ScoreWidget)
	{
		ScoreWidget->AddToViewport();
	}
}

void AMergeTownPlayerController::HideGameplayUI()
{
	if (ScoreWidget)
	{
		ScoreWidget->RemoveFromParent();
		ScoreWidget = nullptr;
	}
}

void AMergeTownPlayerController::ShowGameOverUI(bool bIsHighScore)
{
	if (GameOverWidgetClass)
	{
		GameOverWidget = CreateWidget<UGameOverWidgetBase>(this, GameOverWidgetClass);
	}

	if (GameOverWidget)
	{
		GameOverWidget->AddToViewport();
		GameOverWidget->SetFinalScore(PlayerScore);
		if (bIsHighScore)
		{
			GameOverWidget->SetIsHighScore(bIsHighScore);
		}
	}
}

void AMergeTownPlayerController::HideGameOverUI()
{
	if (GameOverWidget)
	{
		GameOverWidget->RemoveFromParent();
		GameOverWidget = nullptr;
	}
}

void AMergeTownPlayerController::ShowMainMenuUI()
{
	if (MainMenuWidgetClass)
	{
		MainMenuWidget = CreateWidget<UMainMenuWidgetBase>(this, MainMenuWidgetClass);
	}

	if (MainMenuWidget)
	{
		MainMenuWidget->AddToViewport();
		LoadHighScore();
		MainMenuWidget->SetHighScore(HighScore);
	}
}

void AMergeTownPlayerController::HideMainMenuUI()
{
		if (MainMenuWidget)
	{
		MainMenuWidget->RemoveFromParent();
		MainMenuWidget = nullptr;
	}
}

void AMergeTownPlayerController::StartGameplay()
{
	SetBoardCameraActive();
	HideMainMenuUI();
	ShowGameplayUI();
	HideGameOverUI();
	ShowTutorial();
}

void AMergeTownPlayerController::ShowTutorial()
{
	if (isFirstGame)
	{
		CreateAndShowNotification(TutorialText[TutorialStep]);
	}
}

void AMergeTownPlayerController::GameOver(bool cleanUpData)
{
	HideGameplayUI();
	if (cleanUpData) {
		CleanUpGridSaveData();
	}
	bool bIsHighScore = false;
	if (PlayerScore > HighScore)
	{
		SaveHighScore();
		bIsHighScore = true;
	}
	ShowGameOverUI(bIsHighScore);
}

void AMergeTownPlayerController::EndGameplay()
{
	HideGameplayUI();
	HideGameOverUI();
	SetMenuCameraActive();
	ShowMainMenuUI();
}

void AMergeTownPlayerController::ShowHowToPlayUI()
{
	if (HowToPlayWidgetClass)
	{
		HowToPlayWidget = CreateWidget<UHowToPlayWidget>(this, HowToPlayWidgetClass);
	}

	if (HowToPlayWidget)
	{
		HowToPlayWidget->AddToViewport();
		HideMainMenuUI();
	}
}

void AMergeTownPlayerController::HideHowToPlayUI()
{
	if (HowToPlayWidget)
	{
		HowToPlayWidget->RemoveFromParent();
		ShowMainMenuUI();
	}
}

void AMergeTownPlayerController::ShowAuthorsUI()
{
	if (AuthorsWidgetClass)
	{
		AuthorsWidget = CreateWidget<UInformationUserWidgetBase>(this, AuthorsWidgetClass);
	}

	if (AuthorsWidget)
	{
		AuthorsWidget->AddToViewport();
		HideMainMenuUI();
	}
}

void AMergeTownPlayerController::HideAuthorsUI()
{
	if (AuthorsWidget)
	{
		AuthorsWidget->RemoveFromParent();
		ShowMainMenuUI();
	}
}

bool AMergeTownPlayerController::IsSoundOn()
{
	return bIsSoundOn;
}

void AMergeTownPlayerController::SetSoundEnabled(bool bNewValue)
{
	bIsSoundOn = bNewValue;

	// Создать экземпляр класса сохранения игры или загрузить существующий
	UMergeHousesSaveGame* SaveGameInstance = Cast<UMergeHousesSaveGame>(UGameplayStatics::CreateSaveGameObject(UMergeHousesSaveGame::StaticClass()));

	// Загрузить сохранённый файл, если он существует
	if (UGameplayStatics::DoesSaveGameExist("SoundSettingsSlot", 0))
	{
		SaveGameInstance = Cast<UMergeHousesSaveGame>(UGameplayStatics::LoadGameFromSlot("SoundSettingsSlot", 0));
	}

	// Установить значение настройки звука в экземпляре сохранения
	SaveGameInstance->bIsSoundEnabled = bNewValue;

	// Сохранить данные настройки
	UGameplayStatics::SaveGameToSlot(SaveGameInstance, "SoundSettingsSlot", 0);

	if (bIsSoundOn)
	{
		PlayBGM();
	}
	else
	{
		StopBGM();
	}
}

void AMergeTownPlayerController::LoadSoundSetting()
{
	// Проверить, существует ли сохранённый файл
	if (UGameplayStatics::DoesSaveGameExist("SoundSettingsSlot", 0))
	{
		// Загрузить сохранённые настройки
		UMergeHousesSaveGame* LoadGameInstance = Cast<UMergeHousesSaveGame>(UGameplayStatics::LoadGameFromSlot("SoundSettingsSlot", 0));
		if (LoadGameInstance)
		{
			// Применить настройку звука
			bIsSoundOn = LoadGameInstance->bIsSoundEnabled;
		}
	}
}

void AMergeTownPlayerController::PlayMoveSound()
{
	if (MoveSound != nullptr && bIsSoundOn)
	{
		UGameplayStatics::PlaySound2D(this, MoveSound);
	}
}

void AMergeTownPlayerController::PlayMergeSound()
{
	if (MergeSound != nullptr && bIsSoundOn)
	{
		UGameplayStatics::PlaySound2D(this, MergeSound);
	}
}

void AMergeTownPlayerController::PlayClickSound()
{
	if (ClickSound != nullptr && bIsSoundOn)
	{
		UGameplayStatics::PlaySound2D(this, ClickSound);
	}
}

void AMergeTownPlayerController::SetupBGM()
{
	BGMAudioComponent->bAutoActivate = false; // Не воспроизводить звук сразу же
	if (BGMAudioComponent != nullptr && BGM != nullptr)
	{
		BGMAudioComponent->SetSound(BGM);
	}
}

void AMergeTownPlayerController::PlayBGM()
{
	if (BGMAudioComponent != nullptr && !BGMAudioComponent->IsPlaying() && bIsSoundOn)
	{
		BGMAudioComponent->Play();
	}
}

void AMergeTownPlayerController::StopBGM()
{
	if (BGMAudioComponent && BGMAudioComponent->IsPlaying())
	{
		BGMAudioComponent->Stop();
	}
}

void AMergeTownPlayerController::LowerBGMVolume()
{
	if (BGMAudioComponent)
	{
		float Volume = BGMAudioComponent->VolumeMultiplier;
		BGMAudioComponent->SetVolumeMultiplier(Volume * 0.25);
	}
}

void AMergeTownPlayerController::RestoreBGMVolume()
{
	if (BGMAudioComponent)
	{
		float Volume = BGMAudioComponent->VolumeMultiplier;
		BGMAudioComponent->SetVolumeMultiplier(Volume * 4);
	}
}

void AMergeTownPlayerController::SetupGameOverMusic()
{
	GameOverAudioComponent->bAutoActivate = false; // Не воспроизводить звук сразу же
	if (GameOverAudioComponent && GameOverCue != nullptr)
	{
		GameOverAudioComponent->SetSound(GameOverCue);
	}
}

void AMergeTownPlayerController::PlayGameOverMusic()
{
	if (GameOverAudioComponent && !GameOverAudioComponent->IsPlaying() && bIsSoundOn)
	{
		GameOverAudioComponent->Play();
	}
}

void AMergeTownPlayerController::StopGameOverMusic()
{
	if (GameOverAudioComponent && GameOverAudioComponent->IsPlaying())
	{
		GameOverAudioComponent->Stop();
	}
}

void AMergeTownPlayerController::SaveGameState(TArray<int32> Values, TArray<int32> ModelIDs, int32 Value)
{
	UMergeHousesSaveGame* SaveGameInstance = Cast<UMergeHousesSaveGame>(UGameplayStatics::CreateSaveGameObject(UMergeHousesSaveGame::StaticClass()));

	if (UGameplayStatics::DoesSaveGameExist("GameDataSlot", 0))
	{
		SaveGameInstance = Cast<UMergeHousesSaveGame>(UGameplayStatics::LoadGameFromSlot("GameDataSlot", 0));
	}

	SaveGameInstance->CellsValues = Values;
	SaveGameInstance->CellsModels = ModelIDs;
	SaveGameInstance->NextModelID = Value;
	SaveGameInstance->CurrentScores = GetScore();

	UGameplayStatics::SaveGameToSlot(SaveGameInstance, "GameDataSlot", 0);
}

bool AMergeTownPlayerController::CheckForSaveState()
{
	return UGameplayStatics::DoesSaveGameExist("GameDataSlot", 0);
}

UMergeHousesSaveGame* AMergeTownPlayerController::LoadGameState()
{
	return Cast<UMergeHousesSaveGame>(UGameplayStatics::LoadGameFromSlot("GameDataSlot", 0));
}

void AMergeTownPlayerController::CleanUpGridSaveData()
{
	if (UGameplayStatics::DoesSaveGameExist("GameDataSlot", 0))
	{
		UGameplayStatics::DeleteGameInSlot("GameDataSlot", 0);
	}
}

void AMergeTownPlayerController::CreateAndShowNotification(const FString& NotificationMessage)
{
	
	// Assuming UNotificationWidget is your widget class
	NotificationWidget = CreateWidget<UNotificationWidget>(this, NotificationWidgetClass);
	if (NotificationWidget)
	{
		if (AMergeHousesGameModeBase* GameMode = Cast<AMergeHousesGameModeBase>(GetWorld()->GetAuthGameMode()))
		{
			GameMode->DisableControlls();
		}

		NotificationWidget->SetNotificationText(NotificationMessage);
		NotificationWidget->AddToViewport();
	}
}

void AMergeTownPlayerController::SaveTutorialState()
{
	UMergeHousesSaveGame* SaveGameInstance = Cast<UMergeHousesSaveGame>(UGameplayStatics::CreateSaveGameObject(UMergeHousesSaveGame::StaticClass()));

	if (UGameplayStatics::DoesSaveGameExist("TutorialSlot", 0))
	{
		SaveGameInstance = Cast<UMergeHousesSaveGame>(UGameplayStatics::LoadGameFromSlot("TutorialSlot", 0));
	}
	
	SaveGameInstance->ShouldShowTutorial = isFirstGame;

	UGameplayStatics::SaveGameToSlot(SaveGameInstance, "TutorialSlot", 0);
}

void AMergeTownPlayerController::LoadTutorialState()
{
	// Проверить, существует ли сохранённый файл
	if (UGameplayStatics::DoesSaveGameExist("TutorialSlot", 0))
	{
		// Загрузить сохранённые настройки
		UMergeHousesSaveGame* LoadGameInstance = Cast<UMergeHousesSaveGame>(UGameplayStatics::LoadGameFromSlot("TutorialSlot", 0));
		if (LoadGameInstance)
		{
			// Применить настройку звука
			isFirstGame = LoadGameInstance->ShouldShowTutorial;
		}
	}
}
