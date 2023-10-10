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

	// Reference to the reset button actor
	class AMenuSign* MenuSign;

	UPROPERTY(EditAnywhere, Category = "Spawning")
		TSubclassOf<AMenuSign> MenuSignBlueprint;
};
