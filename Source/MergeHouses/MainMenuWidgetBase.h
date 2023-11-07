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

private:

	int32 HighScore = 0;

public:
	
	UFUNCTION(Blueprintcallable, Category = "Gameplay")
		void StartGame();

	UFUNCTION(Blueprintcallable, Category = "Data")
		FText GetHighScoreText() const;

	UFUNCTION(Blueprintcallable, Category = "Data")
		void SetHighScore(int32 ScoresToSet);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
		class USoundCue* ClickSound;

	UFUNCTION(BlueprintCallable, Category = "UI")
		void ShowHowToPlay();

	UFUNCTION(BlueprintCallable, Category = "UI")
		void ShowAuthors();
};
