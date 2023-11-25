// Copyright Epic Games, Inc. All Rights Reserved.


#include "MergeHousesGameModeBase.h"
#include "MenuSign.h"
#include "GameBoard.h"
#include "MergeTownPawn.h"
#include "EngineUtils.h"
#include "Camera/CameraActor.h"
#include "MergeTownPlayerController.h"
#include "TableTopBoard.h"
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
    if (AMergeTownPawn* PlayerPawn = Cast<AMergeTownPawn>(GetWorld()->GetFirstPlayerController()->GetPawn()))
    {
        PlayerPawn->RemoveGameplayMappingContext();
    }
    AMergeTownPlayerController* PlayerController = Cast<AMergeTownPlayerController>(GetWorld()->GetFirstPlayerController());

    if (PlayerController && PlayerController->IsMusicOn())
    {
        PlayerController->LowerBGMVolume();
        PlayerController->PlayGameOverMusic();
    }

    if (PlayerController)
    {
        PlayerController->GameOver();
    }

    // Set a delay for calling GameOver on PlayerController
    float DelayInSeconds = 5.f;
    FTimerHandle TimerHandle;
    FTimerDelegate TimerDelegate;

    TimerDelegate.BindLambda([this]()
        {
            if (AMergeTownPlayerController* PlayerController = Cast<AMergeTownPlayerController>(GetWorld()->GetFirstPlayerController()))
            {
                if (PlayerController->IsMusicOn())
                {
                    PlayerController->RestoreBGMVolume();
                    PlayerController->StopGameOverMusic();
                }
            }
        });

    GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, DelayInSeconds, false);
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
}

void AMergeHousesGameModeBase::Restart()
{
    GameOver();
    StartGameplay();
}

void AMergeHousesGameModeBase::SetGameBoard()
{
    // Find the MenuSign in the level
    for (TActorIterator<AGameBoard> It(GetWorld()); It; ++It)
    {
        GameBoardReference = *It;
        break; // exit the loop once the first MenuSign is found
    }

    for (TActorIterator<ATableTopBoard> It(GetWorld()); It; ++It)
    {
        TableTopBoardReference = *It;
        break;
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

        // Check if the camera has the 'Camera' tag
        if (Camera->ActorHasTag(FName("Camera")))
        {
            // Further check for 'Menu' or 'Board' tags
            if (Camera->ActorHasTag(FName("Menu")))
            {
                Camera_Menu = Camera;
            }
            else if (Camera->ActorHasTag(FName("Board")))
            {
                Camera_Board = Camera;
            }
        }
    }
}
