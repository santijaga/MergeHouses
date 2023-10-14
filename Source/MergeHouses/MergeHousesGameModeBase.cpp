// Copyright Epic Games, Inc. All Rights Reserved.


#include "MergeHousesGameModeBase.h"
#include "MenuSign.h"
#include "GameBoard.h"
#include "MergeTownPawn.h"
#include "EngineUtils.h"

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

    // Find the MenuSign in the level
    for (TActorIterator<AMenuSign> It(GetWorld()); It; ++It)
    {
        MenuSign = *It;
        break; // exit the loop once the first MenuSign is found
    }

    if (!MenuSign)
    {
        UE_LOG(LogTemp, Warning, TEXT("MenuSign not found in the level!"));
    }
    else
    {
        MenuSign->SetGameBoardReference(GameBoardReference);
    }

    if (AMergeTownPawn* PlayerPawn = Cast<AMergeTownPawn>(GetWorld()->GetFirstPlayerController()->GetPawn()))
    {
        PlayerPawn->SetGameBoardReference(GameBoardReference);
    }
}
