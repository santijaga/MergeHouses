// Copyright Epic Games, Inc. All Rights Reserved.


#include "MergeHousesGameModeBase.h"
#include "MenuSign.h"
#include "GameBoard.h"
#include "MergeTownPawn.h"
#include "EngineUtils.h"
#include "Camera/CameraActor.h"
#include "MergeTownPlayerController.h"
#include "TableTopBoard.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"

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

void AMergeHousesGameModeBase::StartGameplay()
{
    if (GameBoardReference)
    {
        GameBoardReference->ResetBoard();
    }

    if (AMergeTownPlayerController* PlayerController = Cast<AMergeTownPlayerController>(GetWorld()->GetFirstPlayerController()))
    {
        PlayerController->StartGameplay();
    }

    if (AMergeTownPawn* PlayerPawn = Cast<AMergeTownPawn>(GetWorld()->GetFirstPlayerController()->GetPawn()))
    {
        PlayerPawn->AddGameplayMappingContext();
    }

    if (TableTopBoardReference)
    {
        TableTopBoardReference->OpenBoard();
    }
}

void AMergeHousesGameModeBase::GameOver()
{
    if (AMergeTownPlayerController* PlayerController = Cast<AMergeTownPlayerController>(GetWorld()->GetFirstPlayerController()))
    {
        PlayerController->GameOver();
    }

    if (AMergeTownPawn* PlayerPawn = Cast<AMergeTownPawn>(GetWorld()->GetFirstPlayerController()->GetPawn()))
    {
        PlayerPawn->RemoveGameplayMappingContext();
    }
}

void AMergeHousesGameModeBase::EndGameplay()
{
    if (AMergeTownPlayerController* PlayerController = Cast<AMergeTownPlayerController>(GetWorld()->GetFirstPlayerController()))
    {
        PlayerController->EndGameplay();
    }

    if (TableTopBoardReference)
    {
        TableTopBoardReference->CloseBoard();
    }

    if (GameBoardReference)
    {
        GameBoardReference->CleanBoard();
    }
}

void AMergeHousesGameModeBase::BeginPlay()
{
	Super::BeginPlay();

    SetGameBoard();
    SetupReferences();
    SetCameras();

    if (BGM != nullptr)
    {
        UGameplayStatics::PlaySoundAtLocation(this, BGM, FVector(0, 0, 0));
    }
}

void AMergeHousesGameModeBase::Restart()
{
    GameOver();
    StartGameplay();
}

void AMergeHousesGameModeBase::UndoMove()
{
    if (GameBoardReference)
    {
        GameBoardReference->UndoMove();
    }
}

bool AMergeHousesGameModeBase::CanUndo()
{
    if (GameBoardReference)
    {
        return GameBoardReference->GetCanUndoMove();
    }
    
    return false;
}

void AMergeHousesGameModeBase::ToggleEditMode()
{
    UE_LOG(LogTemp, Warning, TEXT("[AMergeHousesGameModeBase] About to toggle edit mode."));
    if (GameBoardReference)
    {
        if (GameBoardReference->IsInEditMode())
        {
            GameBoardReference->TurnOffEditMode();
        }
        else
        {
            GameBoardReference->TurnOnEditMode();
        }
    }
    UE_LOG(LogTemp, Warning, TEXT("[AMergeHousesGameModeBase] Edit mode toggled."));
}

void AMergeHousesGameModeBase::RemoveElement(int ID)
{
    UE_LOG(LogTemp, Warning, TEXT("[AMergeHousesGameModeBase] About to remove element"));
    if (GameBoardReference)
    {
        if (GameBoardReference->IsInEditMode())
        {
            GameBoardReference->RemoveElement(ID);
            GameBoardReference->TurnOffEditMode();
        }
    }
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
        UE_LOG(LogTemp, Warning, TEXT("[AMergeHousesGameModeBase] GameBoard not found in the level!"));
    }

    for (TActorIterator<ATableTopBoard> It(GetWorld()); It; ++It)
    {
        TableTopBoardReference = *It;
        break;
    }

    if (!TableTopBoardReference)
    {
        UE_LOG(LogTemp, Warning, TEXT("Table Top Board not found in the level!"));
    }
}


void AMergeHousesGameModeBase::SetupReferences()
{
    if (AMergeTownPawn* PlayerPawn = Cast<AMergeTownPawn>(GetWorld()->GetFirstPlayerController()->GetPawn()))
    {
        PlayerPawn->SetGameBoardReference(GameBoardReference);
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