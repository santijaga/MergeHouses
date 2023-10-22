// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputActionValue.h"
#include "MergeTownPawn.generated.h"

class AMenuSign;
class ACameraActor;

UCLASS()
class MERGEHOUSES_API AMergeTownPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMergeTownPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
		class UInputMappingContext* GamePlayMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
		class UInputAction* MoveAction;

	// Reference to the GameBoard
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameBoard")
		class AGameBoard* GameBoardReference;

	void MakeMove(const FInputActionValue& Value);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void SetGameBoardReference(AGameBoard* GameBoard);

	UFUNCTION()
		void AddGameplayMappingContext();

	UFUNCTION()
		void RemoveGameplayMappingContext();
};
