// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MenuSign.generated.h"

UCLASS()
class MERGEHOUSES_API AMenuSign : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMenuSign();

	// Reference to the GameBoard
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameBoard")
		class AGameBoard* GameBoardReference;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	  
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Click/Tap functions
	virtual void NotifyActorOnClicked(FKey ButtonPressed) override;
#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

	UFUNCTION(BlueprintCallable, Category = "Configuration")
		void SetGameBoardReference(AGameBoard* BoardReference);
};
