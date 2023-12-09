// Fill out your copyright notice in the Description page of Project Settings.


#include "NotificationWidget.h"
#include "MergeTownPlayerController.h"

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
		}
	}

	this->RemoveFromParent();
}

void UNotificationWidget::SetNotificationText(const FString& InNotificationText)
{
	NotificationText = InNotificationText;
}
