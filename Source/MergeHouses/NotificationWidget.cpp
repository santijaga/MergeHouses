// Fill out your copyright notice in the Description page of Project Settings.


#include "NotificationWidget.h"
#include "MergeTownPlayerController.h"
#include "MergeHousesGameModeBase.h"

void UNotificationWidget::CloseNotification()
{
	if (AMergeTownPlayerController* PlayerController = Cast<AMergeTownPlayerController>(GetWorld()->GetFirstPlayerController()))
	{
		PlayerController->TutorialStep = PlayerController->TutorialStep + 1;
		if (PlayerController->TutorialStep <= PlayerController->TutorialSteps) {
			PlayerController->CreateAndShowNotification(PlayerController->TutorialText[PlayerController->TutorialStep]);
		}
		else
		{
			PlayerController->isFirstGame = false;
			PlayerController->SaveTutorialState();
			if (AMergeHousesGameModeBase* GameMode = Cast<AMergeHousesGameModeBase>(GetWorld()->GetAuthGameMode()))
			{
				GameMode->EnableControlls();
			}
		}
	}

	this->RemoveFromParent();
}

void UNotificationWidget::SetNotificationText(const FString& InNotificationText)
{
	NotificationText = InNotificationText;
}
