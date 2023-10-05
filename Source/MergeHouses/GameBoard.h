// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameBoard.generated.h"

USTRUCT(BlueprintType)
struct FBoardCell
{
    GENERATED_BODY()

    int32 Value;           // Value of the cell
    int32 ModelID;         // ID of the 3D model for the cell

    FBoardCell() : Value(0), ModelID(0) {}  // Default Constructor
};

UCLASS()
class MERGEHOUSES_API AGameBoard : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameBoard();

    const int32 BOARD_SIZE = 4; // Size of the game board

    TArray<TArray<FBoardCell>> Board; // 2D array to represent the game board

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Function to initialize the game board with zeros
    void InitializeBoard();

    // Function to generate a random position (row, col) for a new cell
    FVector2D GenerateRandomPosition();

    // Function to make game move
    UFUNCTION(BlueprintCallable, Category = "Moving")
        bool MakeMove(float x, float y);

    // Function to add a new random cell (either 2 or 4) to the board
    bool AddRandomCell();

    // Function to move cells to the left
    bool MoveLeft();

    // Function to move cells to the right
    bool MoveRight();

    // Function to move cells up
    bool MoveUp();

    // Function to move cells down
    bool MoveDown();

    UFUNCTION(BlueprintCallable, Category = "2048")
        void PrintBoardToScreen();

private:
    int32 nextElementIndex = 0; // Index of element on the board

    int32 nextModelID = 0; // ID to assign for newly created 3D grid element
};
