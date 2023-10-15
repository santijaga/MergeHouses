// Copyright Epic Games, Inc. All Rights Reserved.


#include "MergeHousesGameModeBase.h"
#include "MenuSign.h"
#include "GameBoard.h"
#include "MergeTownPawn.h"
#include "EngineUtils.h"
#include "Camera/CameraActor.h"

AMergeHousesGameModeBase::AMergeHousesGameModeBase()
{
    DefaultPawnClass = AMergeTownPawn::StaticClass();
}

ACameraActor* AMergeHousesGameModeBase::GetMenuCameraReference()
{
    return Camera_Menu;
}

ACameraActor* AMergeHousesGameModeBase::GetBoardCameraReference()
{
    return Camera_Board;
}

void AMergeHousesGameModeBase::BeginPlay()
{
	Super::BeginPlay();

    SetGameBoard();
    SetMenuSign();
    SetupReferences();
    SetCameras();
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

void AMergeHousesGameModeBase::SetCameras()
{
    for (TActorIterator<ACameraActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
    {
        ACameraActor* Camera = *ActorItr;

        // Check the tags or names of the camera and assign
        if (Camera->GetActorLabel() == "Camera_MenuCamera")
        {
            Camera_Menu = Camera;
        }
        else if (Camera->GetActorLabel() == "Camera_BoardCamera")
        {
            Camera_Board = Camera;
        }
    }

    // Ensure we found our cameras
    if (!Camera_Menu || !Camera_Board)
    {
        UE_LOG(LogTemp, Warning, TEXT("One or more cameras not found!"));
    }
}