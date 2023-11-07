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

void UMainMenuWidgetBase::ShowAuthors()
{
	if (AMergeTownPlayerController* Controller = Cast<AMergeTownPlayerController>(GetWorld()->GetFirstPlayerController()))
	{
		Controller->ShowAuthorsUI();
	}
}