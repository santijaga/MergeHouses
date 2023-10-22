// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MergeTownPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class MERGEHOUSES_API AMergeTownPlayerController : public APlayerController
{
	GENERATED_BODY()

private:

	// Store current game scores
	UPROPERTY()
		int32 PlayerScore = 0;

	UFUNCTION()
		void PrintScoresToScreen();

	class UMainWidgetBase* ScoreWidget;
	class UGameOverWidgetBase* GameOverWidget;
	class UMainMenuWidgetBase* MainMenuWidget;

public:
	UPROPERTY(EditAnywhere, Category = Camera)
		float CameraBlendSpeed = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
		TSubclassOf<UUserWidget> ScoreWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
		TSubclassOf<UUserWidget> GameOverWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
		TSubclassOf<UUserWidget> MainMenuWidgetClass;

	AMergeTownPlayerController();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	void SetMenuCameraActive();
	void SetBoardCameraActive();

	// Get player's current scores
	int32 GetScore();
	
	// Add scores to player's current scores
	void AddScores(int32 PointsToAdd);

	// Set value to player's current scores
	void SetScores(int32 PointToSet);

	// Reset player's current scores
	void ResetScores();

	UFUNCTION(BlueprintCallable, Category = UI)
		void ShowGameplayUI();

	UFUNCTION(BlueprintCallable, Category = UI)
		void HideGameplayUI();

	UFUNCTION(BlueprintCallable, Category = UI)
		void ShowGameOverUI();

	UFUNCTION(BlueprintCallable, Category = UI)
		void HideGameOverUI();

	UFUNCTION(BlueprintCallable, Category = UI)
		void ShowMainMenuUI();

	UFUNCTION(BlueprintCallable, Category = UI)
		void HideMainMenuUI();

	UFUNCTION(BlueprintCallable, Category = Gameplay)
		void StartGameplay();

	UFUNCTION(BlueprintCallable, Category = Gameplay)
		void GameOver();

	UFUNCTION(BlueprintCallable, Category = Gameplay)
		void EndGameplay();
};
