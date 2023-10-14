// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputActionValue.h"
#include "MergeTownPawn.generated.h"

class AMenuSign;

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

	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category = Camera)
		class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category = Camera)
		class UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pawn Movement")
		float PawnMovingSpeed = 2000.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pawn Movement")
		float RotationSpeed = 50.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pawn Movement")
		float SpringArmMovingSpeed = 500.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pawn Movement")
		float SpringArmLengthSpeed = 5.0f;

	UFUNCTION(BlueprintCallable, Category = Move)
		void MoveToBoard(FVector NewTargetLocation);

	UFUNCTION()
		void SetGameBoardReference(AGameBoard* GameBoard);

	UFUNCTION()
		void SetMenuSignReference(AMenuSign* MenuSign);

private:
	AMenuSign* MenuSignReference;

	UPROPERTY()
		FVector TargetLocation;

	UPROPERTY()
		FVector SpringArmOffset;

	UPROPERTY()
		FRotator SpringArmRotation;

	UPROPERTY()
		bool bIsMovingToTarget;

	UPROPERTY()
		float SpringArmLength = 0.f;
};
