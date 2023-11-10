// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameOverWidgetBase.generated.h"

/**
 * 
 */
UCLASS()
class MERGEHOUSES_API UGameOverWidgetBase : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, Category = "Game Over")
		int32 FinalScore = 0;

	UPROPERTY(BlueprintReadWrite, Category = "Game Over")
		bool bIsHighScore = false;

	UFUNCTION(Blueprintcallable, Category = "Game Over")
		void SetFinalScore(int32 ScoresToSet);

	UFUNCTION(Blueprintcallable, Category = "Game Over")
		void RestartGame();

	UFUNCTION(Blueprintcallable, Category = "Game Over")
		void ReturnToMainMenu();

	UFUNCTION(Blueprintcallable, Category = "Game Over")
		void SetIsHighScore(bool ValueToSet);
};
