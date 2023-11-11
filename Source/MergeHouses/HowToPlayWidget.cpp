// Fill out your copyright notice in the Description page of Project Settings.


#include "HowToPlayWidget.h"
#include "MergeTownPlayerController.h"

void UHowToPlayWidget::NextPage()
{
	UE_LOG(LogTemp, Warning, TEXT("[How To Play] About to select next page."));
	UE_LOG(LogTemp, Warning, TEXT("[How To Play] Current page index is %d from %d"), CurrentPageIndex, TotalPages - 1);
	if (CurrentPageIndex < TotalPages - 1)
	{
		CurrentPageIndex++;
		UE_LOG(LogTemp, Warning, TEXT("[How To Play] New page index is %d"), CurrentPageIndex);
		UE_LOG(LogTemp, Warning, TEXT("[How To Play] Next page selected successfully."));
		
		if (AMergeTownPlayerController* Controller = Cast<AMergeTownPlayerController>(GetWorld()->GetFirstPlayerController()))
		{
			Controller->PlayClickSound();
		}
	}
	
}

void UHowToPlayWidget::PreviousPage()
{
	UE_LOG(LogTemp, Warning, TEXT("[How To Play] About to select previous page."));
	UE_LOG(LogTemp, Warning, TEXT("[How To Play] Current page index is %d from %d"), CurrentPageIndex, TotalPages - 1);
	if (CurrentPageIndex > 0)
	{
		CurrentPageIndex--;
		UE_LOG(LogTemp, Warning, TEXT("[How To Play] New page index is %d"), CurrentPageIndex);
		UE_LOG(LogTemp, Warning, TEXT("[How To Play] Previous page selected successfully."));

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
