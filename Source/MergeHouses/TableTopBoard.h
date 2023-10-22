// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TableTopBoard.generated.h"

UCLASS()
class MERGEHOUSES_API ATableTopBoard : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATableTopBoard();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Mesh")
		class USkeletalMeshComponent* MeshComponent;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "State")
		bool bIsOpened = false;

	UFUNCTION(BlueprintCallable, Category = "State")
		void OpenBoard();

	UFUNCTION(BlueprintCallable, Category = "State")
		void CloseBoard();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
