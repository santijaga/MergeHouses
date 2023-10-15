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

    SetGameBoard();
    SetMenuSign();
    SetupReferences();
}

void AMergeHousesGameModeBase::SetGameBoard()
{
    // Find the MenuSign in the level
    for (TActorIterator<AGameBoard> It(GetWorld()); It; ++It)
    {
        GameBoardReference = *It;
        break; // exit the loop once the first MenuSign is found
    }

    if (!GameBoardReference)
    {
        UE_LOG(LogTemp, Warning, TEXT("GameBoard not found in the level!"));
    }
}

void AMergeHousesGameModeBase::SetMenuSign()
{
    // Find the MenuSign in the level
    for (TActorIterator<AMenuSign> It(GetWorld()); It; ++It)
    {
        MenuSignReference = *It;
        break; // exit the loop once the first MenuSign is found
    }

    if (!MenuSignReference)
    {
        UE_LOG(LogTemp, Warning, TEXT("MenuSign not found in the level!"));
    }
}


void AMergeHousesGameModeBase::SetupReferences()
{
    if (AMergeTownPawn* PlayerPawn = Cast<AMergeTownPawn>(GetWorld()->GetFirstPlayerController()->GetPawn()))
    {
        PlayerPawn->SetGameBoardReference(GameBoardReference);
        PlayerPawn->SetMenuSignReference(MenuSignReference);
    }

    if (MenuSignReference)
    {
        MenuSignReference->SetGameBoardReference(GameBoardReference);
    }
}