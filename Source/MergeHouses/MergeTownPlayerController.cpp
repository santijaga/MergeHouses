// Fill out your copyright notice in the Description page of Project Settings.

#include "MergeTownPlayerController.h"

AMergeTownPlayerController::AMergeTownPlayerController()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
}

void AMergeTownPlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetInputMode(FInputModeGameAndUI());
}