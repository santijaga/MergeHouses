// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainWidgetBase.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class MERGEHOUSES_API UMainWidgetBase : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = UI)
		void UpdateScores(int32 NewScores);

	UFUNCTION(BlueprintCallable, Category = UI)
		void OpenMenu();

	UFUNCTION(BlueprintCallable, Category = UI)
		void CloseMenu();

	UFUNCTION(Blueprintcallable, Category = "Game Over")
		void RestartGame();

	UFUNCTION(Blueprintcallable, Category = "Game Over")
		void ReturnToMainMenu();

	UFUNCTION(Blueprintcallable, Category = "Gameplay")
		void UndoMove();

	UFUNCTION(Blueprintcallable, Category = "Gameplay")
		void ToggleEditMode();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		int32 CurrentScore;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		bool bIsMenuOpened = false;
};
