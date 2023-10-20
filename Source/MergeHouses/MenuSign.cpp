// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuSign.h"
#include "MergeTownPawn.h"
#include "GameBoard.h"
#include "MergeHousesGameModeBase.h"

// Sets default values
AMenuSign::AMenuSign()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMenuSign::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void AMenuSign::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMenuSign::NotifyActorOnClicked(FKey ButtonPressed)
{
    Super::NotifyActorOnClicked(ButtonPressed);

    if (AMergeHousesGameModeBase* GameMode = Cast<AMergeHousesGameModeBase>(GetWorld()->GetAuthGameMode()))
    {
        GameMode->StartGameplay();
    }
}

#if WITH_EDITOR
void AMenuSign::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
    Super::PostEditChangeProperty(PropertyChangedEvent);
}
#endif
