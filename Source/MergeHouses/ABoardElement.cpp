// Fill out your copyright notice in the Description page of Project Settings.


#include "ABoardElement.h"
#include "GameBoard.h"

// Sets default values
AABoardElement::AABoardElement()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AABoardElement::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AABoardElement::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    bool found = false;
    for (int row = 0; row < GameBoard->BoardSize && !found; ++row)
    {
        for (int col = 0; col < GameBoard->BoardSize; ++col)
        {
            FBoardCell& cell = GameBoard->Board[row][col];
            if (cell.ModelID == ID)
            {
                found = true;
                // Move to the new position
                MoveToPosition(row, col);
                // Set the value to the cell's value
                Value = cell.Value;
                break;
            }
        }
    }

    if (!found)
    {
        // Destroy the actor if not found on the board
        Destroy();
    }
}

void AABoardElement::MoveToPosition(int row, int col)
{
    if (!GameBoard)
    {
        UE_LOG(LogTemp, Warning, TEXT("GameBoard reference is null for BoardElement"));
        return;
    }

    FVector BoardLocation = GameBoard->GetActorLocation();
    FRotator BoardRotation = GameBoard->GetActorRotation();

    FVector NewPosition = BoardLocation + FVector(CellSize * col, CellSize * row, 0);

    NewPosition.Z = GetActorLocation().Z;

    SetActorLocationAndRotation(NewPosition, BoardRotation);
}

