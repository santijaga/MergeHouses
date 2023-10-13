// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuSign.h"
#include "MergeTownPawn.h"
#include "GameBoard.h"

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

    FVector startLocation = FVector(-2000.0f, 0.0f, 0.0f);
    FRotator startRotation = FRotator(0, 90, 0);
    FTransform startTransform(startRotation, startLocation);
    SetActorTransform(startTransform);

    PawnReference = Cast<AMergeTownPawn>(GetWorld()->GetFirstPlayerController()->GetPawn());
}

// Called every frame
void AMenuSign::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMenuSign::NotifyActorOnClicked(FKey ButtonPressed)
{
    Super::NotifyActorOnClicked(ButtonPressed);

    // Call ResetBoard from the GameBoard reference
    if (GameBoardReference)
    {
        GameBoardReference->ResetBoard();
    }

    if (PawnReference)
    {
        FVector BoardLocation = GameBoardReference->GetActorLocation();
        PawnReference->MoveToBoard(BoardLocation);
    }
}

#if WITH_EDITOR
void AMenuSign::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
    Super::PostEditChangeProperty(PropertyChangedEvent);
}
#endif

void AMenuSign::SetGameBoardReference(AGameBoard* BoardReference)
{
    GameBoardReference = BoardReference;
}
