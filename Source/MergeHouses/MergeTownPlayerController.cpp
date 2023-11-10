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
}

void AMergeTownPlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetInputMode(FInputModeGameAndUI());
	SetViewTarget(Cast<AMergeHousesGameModeBase>(GetWorld()->GetAuthGameMode())->GetMenuCameraReference());
	ShowMainMenuUI();
	LoadSoundSetting();
	LoadMusicSetting();
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
	UE_LOG(LogTemp, Warning, TEXT("AMergeTownPlayerController: About to set menu camera active."));
	SetViewTargetWithBlend(Cast<AMergeHousesGameModeBase>(GetWorld()->GetAuthGameMode())->GetMenuCameraReference(), CameraBlendSpeed);
	UE_LOG(LogTemp, Warning, TEXT("AMergeTownPlayerController: Menu camera set successfully."));
}

void AMergeTownPlayerController::SetBoardCameraActive()
{
	UE_LOG(LogTemp, Warning, TEXT("AMergeTownPlayerController: About to set board camera active."));
	SetViewTargetWithBlend(Cast<AMergeHousesGameModeBase>(GetWorld()->GetAuthGameMode())->GetBoardCameraReference(), CameraBlendSpeed);
	UE_LOG(LogTemp, Warning, TEXT("AMergeTownPlayerController: Board camera set successfully."));
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
	UE_LOG(LogTemp, Warning, TEXT("AMergeTownPlayerController: Stored scores: %d."), StoredScores);
}

void AMergeTownPlayerController::RestoreScores()
{
	SetScores(StoredScores);
}

void AMergeTownPlayerController::ShowGameplayUI()
{
	UE_LOG(LogTemp, Warning, TEXT("AMergeTownPlayerController: About to show gameplay UI."));
	if (ScoreWidgetClass)
	{
		ScoreWidget = CreateWidget<UMainWidgetBase>(this, ScoreWidgetClass);
	}

	if (ScoreWidget)
	{
		ScoreWidget->AddToViewport();
	}
	UE_LOG(LogTemp, Warning, TEXT("AMergeTownPlayerController: Gameplay UI show successfully."));
}

void AMergeTownPlayerController::HideGameplayUI()
{
	UE_LOG(LogTemp, Warning, TEXT("AMergeTownPlayerController: About to hide gameplay UI."));
	if (ScoreWidget)
	{
		ScoreWidget->RemoveFromParent();
		ScoreWidget = nullptr;
	}
	UE_LOG(LogTemp, Warning, TEXT("AMergeTownPlayerController: Gameplay UI hide successfully."));
}

void AMergeTownPlayerController::ShowGameOverUI(bool bIsHighScore)
{
	UE_LOG(LogTemp, Warning, TEXT("AMergeTownPlayerController: About to show game over UI."));
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
	UE_LOG(LogTemp, Warning, TEXT("AMergeTownPlayerController: Game over UI show successfully."));
}

void AMergeTownPlayerController::HideGameOverUI()
{
	UE_LOG(LogTemp, Warning, TEXT("AMergeTownPlayerController: About to hide game over UI."));
	if (GameOverWidget)
	{
		GameOverWidget->RemoveFromParent();
		GameOverWidget = nullptr;
	}
	UE_LOG(LogTemp, Warning, TEXT("AMergeTownPlayerController: Game over UI hide successfully."));
}

void AMergeTownPlayerController::ShowMainMenuUI()
{
	UE_LOG(LogTemp, Warning, TEXT("AMergeTownPlayerController: About to show main menu UI."));
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
	UE_LOG(LogTemp, Warning, TEXT("AMergeTownPlayerController: Main menu UI show successfully."));
}

void AMergeTownPlayerController::HideMainMenuUI()
{
	UE_LOG(LogTemp, Warning, TEXT("AMergeTownPlayerController: About to hide main menu UI."));
	if (MainMenuWidget)
	{
		MainMenuWidget->RemoveFromParent();
		MainMenuWidget = nullptr;
	}
	UE_LOG(LogTemp, Warning, TEXT("AMergeTownPlayerController: Main menu UI hide successfully."));
}

void AMergeTownPlayerController::StartGameplay()
{
	UE_LOG(LogTemp, Warning, TEXT("AMergeTownPlayerController: About to start gameplay."));
	SetBoardCameraActive();
	HideMainMenuUI();
	ShowGameplayUI();
	HideGameOverUI();
	ResetScores();
	UE_LOG(LogTemp, Warning, TEXT("AMergeTownPlayerController: Gameplay start successfully."));
}

void AMergeTownPlayerController::GameOver()
{
	UE_LOG(LogTemp, Warning, TEXT("AMergeTownPlayerController: About game over."));
	HideGameplayUI();
	bool bIsHighScore = false;
	if (PlayerScore > HighScore)
	{
		SaveHighScore();
		bIsHighScore = true;
	}
	ShowGameOverUI(bIsHighScore);
	UE_LOG(LogTemp, Warning, TEXT("AMergeTownPlayerController: Game over successfully."));
}

void AMergeTownPlayerController::EndGameplay()
{
	UE_LOG(LogTemp, Warning, TEXT("AMergeTownPlayerController: About to end gameplay."));
	HideGameplayUI();
	HideGameOverUI();
	SetMenuCameraActive();
	ShowMainMenuUI();
	UE_LOG(LogTemp, Warning, TEXT("AMergeTownPlayerController: Gameplay end successfully."));
}

void AMergeTownPlayerController::ShowHowToPlayUI()
{
	UE_LOG(LogTemp, Warning, TEXT("AMergeTownPlayerController: About to show how to play UI."));
	if (HowToPlayWidgetClass)
	{
		HowToPlayWidget = CreateWidget<UHowToPlayWidget>(this, HowToPlayWidgetClass);
	}

	if (HowToPlayWidget)
	{
		HowToPlayWidget->AddToViewport();
		HideMainMenuUI();
	}
	UE_LOG(LogTemp, Warning, TEXT("AMergeTownPlayerController: How to play UI show successfully."));
}

void AMergeTownPlayerController::HideHowToPlayUI()
{
	UE_LOG(LogTemp, Warning, TEXT("AMergeTownPlayerController: About to hide how to play UI."));
	if (HowToPlayWidget)
	{
		HowToPlayWidget->RemoveFromParent();
		ShowMainMenuUI();
	}
	UE_LOG(LogTemp, Warning, TEXT("AMergeTownPlayerController: How to play UI hide successfully."));
}

void AMergeTownPlayerController::ShowAuthorsUI()
{
	UE_LOG(LogTemp, Warning, TEXT("AMergeTownPlayerController: About to show Authors UI"));
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

bool AMergeTownPlayerController::IsMusicOn()
{
	return bIsMusicOn;
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
}

void AMergeTownPlayerController::SetMusicEnabled(bool bNewValue)
{
	bIsMusicOn = bNewValue;

	// Создать экземпляр класса сохранения игры или загрузить существующий
	UMergeHousesSaveGame* SaveGameInstance = Cast<UMergeHousesSaveGame>(UGameplayStatics::CreateSaveGameObject(UMergeHousesSaveGame::StaticClass()));

	// Загрузить сохранённый файл, если он существует
	if (UGameplayStatics::DoesSaveGameExist("MusicSettingsSlot", 0))
	{
		SaveGameInstance = Cast<UMergeHousesSaveGame>(UGameplayStatics::LoadGameFromSlot("MusicSettingsSlot", 0));
	}

	// Установить значение настройки звука в экземпляре сохранения
	SaveGameInstance->bIsMusicEnabled = bNewValue;

	// Сохранить данные настройки
	UGameplayStatics::SaveGameToSlot(SaveGameInstance, "MusicSettingsSlot", 0);
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

void AMergeTownPlayerController::LoadMusicSetting()
{
	// Проверить, существует ли сохранённый файл
	if (UGameplayStatics::DoesSaveGameExist("MusicSettingsSlot", 0))
	{
		// Загрузить сохранённые настройки
		UMergeHousesSaveGame* LoadGameInstance = Cast<UMergeHousesSaveGame>(UGameplayStatics::LoadGameFromSlot("MusicSettingsSlot", 0));
		if (LoadGameInstance)
		{
			// Применить настройку звука
			bIsMusicOn = LoadGameInstance->bIsMusicEnabled;
		}
	}
}

void AMergeTownPlayerController::PlayMoveSound()
{
	if (MoveSound != nullptr)
	{
		UGameplayStatics::PlaySound2D(this, MoveSound);
	}
}

void AMergeTownPlayerController::PlayMergeSound()
{
	if (MergeSound != nullptr)
	{
		UGameplayStatics::PlaySound2D(this, MergeSound);
	}
}

void AMergeTownPlayerController::PlayClickSound()
{
	if (ClickSound != nullptr)
	{
		UGameplayStatics::PlaySound2D(this, ClickSound);
	}
}
