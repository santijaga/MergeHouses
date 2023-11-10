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
#include "Components/AudioComponent.h"

AMergeHousesGameModeBase::AMergeHousesGameModeBase()
{
    DefaultPawnClass = AMergeTownPawn::StaticClass();

    BGMAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("BGMComponent"));
    GameOverAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("GameOverAudioComponent"));
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
        LowerBGMVolume();
        PlayGameOverMusic();
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
                    RestoreBGMVolume();
                    StopGameOverMusic();
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

    SetupBGM();

    bool bIsMusicOn = false;
    if (AMergeTownPlayerController* PlayerController = Cast<AMergeTownPlayerController>(GetWorld()->GetFirstPlayerController()))
    {
        bIsMusicOn = PlayerController->IsMusicOn();
    }
    if (bIsMusicOn)
    {
        PlayBGM();
    }

    SetupGameOverMusic();
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

bool AMergeHousesGameModeBase::IsEditModeActive()
{
    if (GameBoardReference)
    {
        return GameBoardReference->IsInEditMode();
    }

    return false;
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

void AMergeHousesGameModeBase::SetupBGM()
{
    BGMAudioComponent->bAutoActivate = false; // Не воспроизводить звук сразу же
    if (BGMAudioComponent && BGM != nullptr)
    {
        BGMAudioComponent->SetSound(BGM);
    }
}

void AMergeHousesGameModeBase::PlayBGM()
{
    UE_LOG(LogTemp, Warning, TEXT("[AMergeHousesGameModeBase] About to Play BGM."));
    if (BGMAudioComponent && !BGMAudioComponent->IsPlaying())
    {
        BGMAudioComponent->Play();
        UE_LOG(LogTemp, Warning, TEXT("[AMergeHousesGameModeBase] BGM Played."));
    }
}

void AMergeHousesGameModeBase::StopBGM()
{
    if (BGMAudioComponent && BGMAudioComponent->IsPlaying())
    {
        BGMAudioComponent->Stop();
    }
}

void AMergeHousesGameModeBase::LowerBGMVolume()
{
    if (BGMAudioComponent)
    {
        float Volume = BGMAudioComponent->VolumeMultiplier;
        BGMAudioComponent->SetVolumeMultiplier(Volume * 0.25);
    }
}

void AMergeHousesGameModeBase::RestoreBGMVolume()
{
    if (BGMAudioComponent)
    {
        float Volume = BGMAudioComponent->VolumeMultiplier;
        BGMAudioComponent->SetVolumeMultiplier(Volume * 4);
    }
}

void AMergeHousesGameModeBase::SetupGameOverMusic()
{
    GameOverAudioComponent->bAutoActivate = false; // Не воспроизводить звук сразу же
    if (GameOverAudioComponent && GameOverCue != nullptr)
    {
        GameOverAudioComponent->SetSound(GameOverCue);
    }
}

void AMergeHousesGameModeBase::PlayGameOverMusic()
{
    if (GameOverAudioComponent && !GameOverAudioComponent->IsPlaying())
    {
        GameOverAudioComponent->Play();
    }
}

void AMergeHousesGameModeBase::StopGameOverMusic()
{
    if (GameOverAudioComponent && GameOverAudioComponent->IsPlaying())
    {
        GameOverAudioComponent->Stop();
    }
}
