// Fill out your copyright notice in the Description page of Project Settings.


#include "HowToPlayWidget.h"
#include "MergeTownPlayerController.h"

void UHowToPlayWidget::NextPage()
{
	if (CurrentPageIndex < TotalPages - 1)
	{
		CurrentPageIndex++;
		
		if (AMergeTownPlayerController* Controller = Cast<AMergeTownPlayerController>(GetWorld()->GetFirstPlayerController()))
		{
			Controller->PlayClickSound();
		}
	}
	
}

void UHowToPlayWidget::PreviousPage()
{
	if (CurrentPageIndex > 0)
	{
		CurrentPageIndex--;
		
		if (AMergeTownPlayerController* Controller = Cast<AMergeTownPlayerController>(GetWorld()->GetFirstPlayerController()))
		{
			Controller->PlayClickSound();
		}
	}
}

void UHowToPlayWidget::CloseScreen()
{
	if (AMergeTownPlayerController* Controller = Cast<AMergeTownPlayerController>(GetWorld()->GetFirstPlayerController()))
	{
		Controller->HideHowToPlayUI();
		Controller->PlayClickSound();
	}
}
