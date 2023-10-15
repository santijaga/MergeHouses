// Fill out your copyright notice in the Description page of Project Settings.

#include "MergeTownPlayerController.h"
#include "MergeHousesGameModeBase.h"
#include "Camera/CameraActor.h"

AMergeTownPlayerController::AMergeTownPlayerController()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
}

void AMergeTownPlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetInputMode(FInputModeGameAndUI());
	SetViewTarget(Cast<AMergeHousesGameModeBase>(GetWorld()->GetAuthGameMode())->GetMenuCameraReference());
}