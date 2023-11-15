// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ABoardElement.generated.h"

class AGameBoard;

UCLASS()
class MERGEHOUSES_API AABoardElement : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AABoardElement();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Board")
		AGameBoard* GameBoard; // A reference to the main board

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Board")
		float CellSize; // Size of each cell on the game board

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Board")
		int ID; // Unique identifier for this board element

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Board")
		int Value; // The value of this board element

private:
	UPROPERTY()
		FVector TargetPosition;

	UPROPERTY()
		FRotator TargetRotation;

	UPROPERTY()
		bool bIsMoving = false;
};
