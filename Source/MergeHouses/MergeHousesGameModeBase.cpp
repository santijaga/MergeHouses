// Copyright Epic Games, Inc. All Rights Reserved.


#include "MergeHousesGameModeBase.h"
#include "MenuSign.h"
#include "GameBoard.h"
#include "MergeTownPawn.h"

AMergeHousesGameModeBase::AMergeHousesGameModeBase()
{
    DefaultPawnClass = AMergeTownPawn::StaticClass();
}

void AMergeHousesGameModeBase::BeginPlay()
{
	Super::BeginPlay();

    if (GameBoardBlueprint)
    {
        FTransform GameBoardSpawnTransform;
        GameBoardReference = GetWorld()->SpawnActor<AGameBoard>(GameBoardBlueprint, GameBoardSpawnTransform);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("GameBoardBlueprint is not set!"));
    }

    if (MenuSignBlueprint) // Check if we have set a blueprint class to spawn
    {
        FTransform SpawnTransform; // Set this to your desired location and rotation
        MenuSign = GetWorld()->SpawnActor<AMenuSign>(MenuSignBlueprint, SpawnTransform);

        MenuSign->SetGameBoardReference(GameBoardReference);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("MenuSignBlueprint is not set!"));
    }

    if (AMergeTownPawn* PlayerPawn = Cast<AMergeTownPawn>(GetWorld()->GetFirstPlayerController()->GetPawn()))
    {
        PlayerPawn->SetGameBoardReference(GameBoardReference);
    }
}
