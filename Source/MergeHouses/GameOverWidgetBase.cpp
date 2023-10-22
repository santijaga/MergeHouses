// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOverWidgetBase.h"
#include "MergeHousesGameModeBase.h"

void UGameOverWidgetBase::SetFinalScore(int32 ScoresToSet)
{
	FinalScore = ScoresToSet;
}

void UGameOverWidgetBase::RestartGame()
{
	if (AMergeHousesGameModeBase* GameMode = Cast<AMergeHousesGameModeBase>(GetWorld()->GetAuthGameMode()))
	{
		GameMode->StartGameplay();
	}
}

void UGameOverWidgetBase::ReturnToMainMenu()
{
	if (AMergeHousesGameModeBase* GameMode = Cast<AMergeHousesGameModeBase>(GetWorld()->GetAuthGameMode()))
	{
		GameMode->EndGameplay();
	}
}

void UGameOverWidgetBase::SetIsHighScore(bool ValueToSet)
{
	bIsHighScore = ValueToSet;
}
