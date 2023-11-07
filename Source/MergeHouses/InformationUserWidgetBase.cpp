// Fill out your copyright notice in the Description page of Project Settings.


#include "InformationUserWidgetBase.h"
#include "MergeTownPlayerController.h"

void UInformationUserWidgetBase::CloseMenu()
{
	if (AMergeTownPlayerController* Controller = Cast<AMergeTownPlayerController>(GetWorld()->GetFirstPlayerController()))
	{
		Controller->HideAuthorsUI();
	}
}