// Fill out your copyright notice in the Description page of Project Settings.


#include "MainWidgetBase.h"
#include "MergeHousesGameModeBase.h"
#include "MergeTownPlayerController.h"

void UMainWidgetBase::UpdateScores(int32 NewScores)
{
	CurrentScore = NewScores;
}

void UMainWidgetBase::OpenMenu()
{
	bIsMenuOpened = true;
	if (AMergeHousesGameModeBase* GameMode = Cast<AMergeHousesGameModeBase>(GetWorld()->GetAuthGameMode()))
	{
		GameMode->DisableControlls();
	}
}

void UMainWidgetBase::CloseMenu()
{
	bIsMenuOpened = false;
	if (AMergeHousesGameModeBase* GameMode = Cast<AMergeHousesGameModeBase>(GetWorld()->GetAuthGameMode()))
	{
		GameMode->EnableControlls();
	}
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

bool UMainWidgetBase::GetIsSoundOn()
{
	if (AMergeTownPlayerController* Controller = Cast<AMergeTownPlayerController>(GetWorld()->GetFirstPlayerController()))
	{
		return Controller->IsSoundOn();
	}
	return false;
}

void UMainWidgetBase::ToggleSound()
{
	if (AMergeTownPlayerController* Controller = Cast<AMergeTownPlayerController>(GetWorld()->GetFirstPlayerController()))
	{
		if (Controller->IsSoundOn())
		{
			Controller->SetSoundEnabled(false);
		}
		else
		{
			Controller->SetSoundEnabled(true);
		}
	}
}

