// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuWidgetBase.h"
#include "MergeHousesGameModeBase.h"

void UMainMenuWidgetBase::StartGame()
{
	if (AMergeHousesGameModeBase* GameMode = Cast<AMergeHousesGameModeBase>(GetWorld()->GetAuthGameMode()))
	{
		GameMode->StartGameplay();
	}
}
