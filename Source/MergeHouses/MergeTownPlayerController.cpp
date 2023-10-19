// Fill out your copyright notice in the Description page of Project Settings.

#include "MergeTownPlayerController.h"
#include "MergeHousesGameModeBase.h"
#include "Camera/CameraActor.h"

void AMergeTownPlayerController::PrintScoresToScreen()
{
	FString ScoresString = FString::Printf(TEXT("Scores: %d"), PlayerScore);

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::White, ScoresString);
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
}

void AMergeTownPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	PrintScoresToScreen();
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
