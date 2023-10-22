// Fill out your copyright notice in the Description page of Project Settings.

#include "MergeTownPlayerController.h"
#include "MergeHousesGameModeBase.h"
#include "Camera/CameraActor.h"
#include "MainWidgetBase.h"
#include "GameOverWidgetBase.h"
#include "MainMenuWidgetBase.h"
#include "MergeHousesSaveGame.h"
#include "Kismet/GameplayStatics.h"

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
	HideGameOverUI();
	SetMenuCameraActive();
	ShowMainMenuUI();
	UE_LOG(LogTemp, Warning, TEXT("AMergeTownPlayerController: Gameplay end successfully."));
}


