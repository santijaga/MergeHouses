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

                // Update target position and rotation
                FVector BoardLocation = GameBoard->GetActorLocation();
                FRotator BoardRotation = GameBoard->GetActorRotation();
                TargetPosition = BoardLocation + FVector(CellSize * col, CellSize * row, 0);
                TargetPosition.Z = GetActorLocation().Z;
                TargetRotation = BoardRotation;
                bIsMoving = true;

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
    else if (bIsMoving)
    {
        FVector NewPosition = FMath::VInterpTo(GetActorLocation(), TargetPosition, DeltaTime, 10.0f);
        FRotator NewRotation = FMath::RInterpTo(GetActorRotation(), TargetRotation, DeltaTime, 10.0f);
        SetActorLocationAndRotation(NewPosition, NewRotation);

        if (GetActorLocation().Equals(TargetPosition, 1.0f) && GetActorRotation().Equals(TargetRotation, 1.0f))
        {
            bIsMoving = false;
        }
    }
}

