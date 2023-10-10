// Copyright Epic Games, Inc. All Rights Reserved.


#include "MergeHousesGameModeBase.h"
#include "MenuSign.h"

void AMergeHousesGameModeBase::BeginPlay()
{
	Super::BeginPlay();

    if (MenuSignBlueprint) // Check if we have set a blueprint class to spawn
    {
        FTransform SpawnTransform; // Set this to your desired location and rotation
        MenuSign = GetWorld()->SpawnActor<AMenuSign>(MenuSignBlueprint, SpawnTransform);

        // Optionally initialize properties of ResetButton
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("MenuSignBlueprint is not set!"));
    }
}
