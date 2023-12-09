// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "MergeHousesSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class MERGEHOUSES_API UMergeHousesSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere, Category = "SaveData")
		int32 SavedHighScore;

	UPROPERTY(VisibleAnywhere, Category = "SaveSettings")
		bool bIsSoundEnabled;

	UPROPERTY(VisibleAnywhere, Category = "SaveSettings")
		bool bIsMusicEnabled;

	UPROPERTY(VisibleAnywhere, Category = "Feature")
		bool bIsUndoAvailable;

	UPROPERTY(VisibleAnywhere, Category = "Feature")
		bool bIsRemoveAvailable;

	UPROPERTY(VisibleAnywhere, Category = "GameData")
		TArray<int32> CellsValues;

	UPROPERTY(VisibleAnywhere, Category = "GameData")
		TArray<int32> CellsModels;

	UPROPERTY(VisibleAnywhere, Category = "GameData")
		int32 NextModelID;

	UPROPERTY(VisibleAnywhere, Category = "GameData")
		int32 CurrentScores;

	UPROPERTY(VisibleAnywhere, Category = "TutorialData")
		bool ShouldShowTutorial;
};
