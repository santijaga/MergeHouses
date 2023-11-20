// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameBoard.generated.h"

class AABoardElement;

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

protected:
    // Engine methods
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

    // Gameplay
    int32 nextElementIndex = 0; // Index of element on the board
    int32 nextModelID = 0; // ID to assign for newly created 3D grid element
    bool bIsGameOver = true;

    void InitializeBoard();
    FVector2D GenerateRandomPosition();
    bool AddRandomCell();
    bool MoveLeft();
    bool MoveRight();
    bool MoveUp();
    bool MoveDown();

    // Properties for control sound
    bool bWasMerge = false;

    UFUNCTION()
        bool IsGameOver();

    UFUNCTION()
        int32 GetElementsCount();

    void AddCells(int32 cellsCountToAdd);

    void SaveBoard();
    void LoadBoard();

public:	
    TArray<TArray<FBoardCell>> Board;

	AGameBoard();

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Board")
        int32 BoardSize = 4;

    UPROPERTY(EditDefaultsOnly, Category = "Board Elements")
        TSubclassOf<AABoardElement> BoardElementClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Board")
        float CellSize = 100.0f;

    UFUNCTION(BlueprintCallable, Category = "Board")
        AABoardElement* SpawnBoardElement(int row, int col, int value, int ID);

    UFUNCTION(BlueprintCallable, Category = "Gameplay")
        void ResetBoard();

    UFUNCTION(BlueprintCallable, Category = "Moving")
        bool MakeMove(float x, float y);

    UFUNCTION(BlueprintCallable, Category = "Board")
        void CleanBoard();
};
