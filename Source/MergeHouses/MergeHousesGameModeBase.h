// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MergeHousesGameModeBase.generated.h"

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
	
	UPROPERTY()
		class AMenuSign* MenuSign;

	class AGameBoard* GameBoardReference;

	UPROPERTY(EditAnywhere, Category = "Spawning")
		TSubclassOf<AGameBoard> GameBoardBlueprint;
};
