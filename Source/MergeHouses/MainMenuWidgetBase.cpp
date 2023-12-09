// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuWidgetBase.h"
#include "MergeHousesGameModeBase.h"
#include "MergeTownPlayerController.h"

void UMainMenuWidgetBase::StartGame()
{
	if (AMergeHousesGameModeBase* GameMode = Cast<AMergeHousesGameModeBase>(GetWorld()->GetAuthGameMode()))
	{
		GameMode->StartGameplay();
	}
}

FText UMainMenuWidgetBase::GetHighScoreText() const
{
	return FText::FromString(FString::Printf(TEXT("%d"), HighScore));
}

void UMainMenuWidgetBase::SetHighScore(int32 ScoresToSet)
{
	HighScore = ScoresToSet;
}

void UMainMenuWidgetBase::ShowHowToPlay()
{
	if (AMergeTownPlayerController* Controller = Cast<AMergeTownPlayerController>(GetWorld()->GetFirstPlayerController()))
	{
		Controller->ShowHowToPlayUI();
	}
}

void UMainMenuWidgetBase::ResetTutorial()
{
	if (AMergeTownPlayerController* Controller = Cast<AMergeTownPlayerController>(GetWorld()->GetFirstPlayerController()))
	{
		Controller->isFirstGame = true;
		Controller->TutorialStep = 0;
		Controller->SaveTutorialState();
	}
}

bool UMainMenuWidgetBase::ShowResetTutorialButton()
{
	if (AMergeTownPlayerController* Controller = Cast<AMergeTownPlayerController>(GetWorld()->GetFirstPlayerController()))
	{
		return !Controller->isFirstGame;
	}

	return false;
}

void UMainMenuWidgetBase::ShowAuthors()
{
	if (AMergeTownPlayerController* Controller = Cast<AMergeTownPlayerController>(GetWorld()->GetFirstPlayerController()))
	{
		Controller->ShowAuthorsUI();
	}
}

bool UMainMenuWidgetBase::GetIsSoundOn()
{
	if (AMergeTownPlayerController* Controller = Cast<AMergeTownPlayerController>(GetWorld()->GetFirstPlayerController()))
	{
		return Controller->IsSoundOn();
	}
	return false;
}

bool UMainMenuWidgetBase::GetIsMusicOn()
{
	if (AMergeTownPlayerController* Controller = Cast<AMergeTownPlayerController>(GetWorld()->GetFirstPlayerController()))
	{
		return Controller->IsMusicOn();
	}
	return false;
}

void UMainMenuWidgetBase::ToggleSound()
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

void UMainMenuWidgetBase::ToggleMusic()
{
	if (AMergeTownPlayerController* Controller = Cast<AMergeTownPlayerController>(GetWorld()->GetFirstPlayerController()))
	{
		if (Controller->IsMusicOn())
		{
			Controller->SetMusicEnabled(false);
		}
		else
		{
			Controller->SetMusicEnabled(true);
		}
	}
}
