// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InformationUserWidgetBase.generated.h"

/**
 * 
 */
UCLASS()
class MERGEHOUSES_API UInformationUserWidgetBase : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, Category = "UI")
		void CloseMenu();
};
