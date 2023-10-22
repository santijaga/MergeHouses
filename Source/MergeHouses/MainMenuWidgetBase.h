// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuWidgetBase.generated.h"

/**
 * 
 */
UCLASS()
class MERGEHOUSES_API UMainMenuWidgetBase : public UUserWidget
{
	GENERATED_BODY()
	
	UFUNCTION(Blueprintcallable, Category = "Gameplay")
		void StartGame();
};
