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

public:
	UPROPERTY(EditAnywhere, Category = Camera)
		float CameraBlendSpeed = 1.f;

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
};
