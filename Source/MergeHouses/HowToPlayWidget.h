// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HowToPlayWidget.generated.h"

/**
 * 
 */
UCLASS()
class MERGEHOUSES_API UHowToPlayWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
		int32 CurrentPageIndex = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
		int32 TotalPages = 6;

public:
	UFUNCTION(BlueprintCallable, Category = "UI")
		void NextPage();

	UFUNCTION(BlueprintCallable, Category = "UI")
		void PreviousPage();

	UFUNCTION(BlueprintCallable, Category = "UI")
		void CloseScreen();
};
