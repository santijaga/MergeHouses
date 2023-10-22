// Fill out your copyright notice in the Description page of Project Settings.


#include "TableTopBoard.h"

// Sets default values
ATableTopBoard::ATableTopBoard()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MeshComponent;
}

void ATableTopBoard::OpenBoard()
{
	bIsOpened = true;
}

void ATableTopBoard::CloseBoard()
{
	bIsOpened = false;
}

// Called when the game starts or when spawned
void ATableTopBoard::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATableTopBoard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

