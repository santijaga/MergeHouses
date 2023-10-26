// Fill out your copyright notice in the Description page of Project Settings.


#include "MainWidgetBase.h"
#include "MergeHousesGameModeBase.h"

void UMainWidgetBase::UpdateScores(int32 NewScores)
{
	CurrentScore = NewScores;
}

void UMainWidgetBase::OpenMenu()
{
	bIsMenuOpened = true;
}

void UMainWidgetBase::CloseMenu()
{
	bIsMenuOpened = false;
}

void UMainWidgetBase::RestartGame()
{
	if (AMergeHousesGameModeBase* GameMode = Cast<AMergeHousesGameModeBase>(GetWorld()->GetAuthGameMode()))
	{
		GameMode->Restart();
	}
}

void UMainWidgetBase::ReturnToMainMenu()
{
	if (AMergeHousesGameModeBase* GameMode = Cast<AMergeHousesGameModeBase>(GetWorld()->GetAuthGameMode()))
	{
		GameMode->GameOver();
		GameMode->EndGameplay();
		CloseMenu();
	}
}

void UMainWidgetBase::UndoMove()
{
	if (AMergeHousesGameModeBase* GameMode = Cast<AMergeHousesGameModeBase>(GetWorld()->GetAuthGameMode()))
	{
		GameMode->UndoMove();
	}
}

void UMainWidgetBase::ToggleEditMode()
{
	UE_LOG(LogTemp, Warning, TEXT("About to toggle edit mode"));
}
