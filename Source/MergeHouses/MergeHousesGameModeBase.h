// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MergeHousesGameModeBase.generated.h"

class ACameraActor;

/**
 * 
 */
UCLASS()
class MERGEHOUSES_API AMergeHousesGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
	virtual void BeginPlay() override;

	AMergeHousesGameModeBase();

public:
	class AGameBoard* GameBoardReference;
	class ATableTopBoard* TableTopBoardReference;

	UFUNCTION()
		ACameraActor* GetMenuCameraReference();

	UFUNCTION()
		ACameraActor* GetBoardCameraReference();

	UFUNCTION()
		void StartGameplay();

	UFUNCTION()
		void GameOver();

	UFUNCTION()
		void EndGameplay();

	UFUNCTION()
		void Restart();

	UFUNCTION()
		void UndoMove();

	UFUNCTION(Blueprintcallable, Category = "Gameplay")
		bool CanUndo();

	UFUNCTION(Blueprintcallable, Category = "Gameplay")
		void ToggleEditMode();

	UFUNCTION(Blueprintcallable, Category = "Gameplay")
		void RemoveElement(int ID);

private:
	void SetGameBoard();
	void SetupReferences();
	void SetCameras();

	ACameraActor* Camera_Menu;
	ACameraActor* Camera_Board;
};
