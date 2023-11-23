// Fill out your copyright notice in the Description page of Project Settings.


#include "MergeTownPawn.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/InputComponent.h"
#include "Components/SceneComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EngineUtils.h"
#include "GameFramework/SpringArmComponent.h"
#include "InputAction.h"
#include "InputActionValue.h"
#include "MenuSign.h"
#include "GameBoard.h"
#include "MergeTownPlayerController.h"

// Sets default values
AMergeTownPawn::AMergeTownPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AMergeTownPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Started, this, &AMergeTownPawn::MakeMove);
	}

	PlayerInputComponent->BindTouch(IE_Pressed, this, &AMergeTownPawn::TouchPressed);
	PlayerInputComponent->BindTouch(IE_Repeat, this, &AMergeTownPawn::TouchMoved);
	PlayerInputComponent->BindTouch(IE_Released, this, &AMergeTownPawn::TouchReleased);
}

// Called when the game starts or when spawned
void AMergeTownPawn::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMergeTownPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMergeTownPawn::MakeMove(const FInputActionValue& Value)
{
	FVector2D MoveValue = Value.Get<FVector2D>();

	if (GameBoardReference)
	{
		GameBoardReference->MakeMove(MoveValue.X, MoveValue.Y);
	}
}

void AMergeTownPawn::SetGameBoardReference(AGameBoard* GameBoard)
{
	GameBoardReference = GameBoard;
}

void AMergeTownPawn::AddGameplayMappingContext()
{
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(GamePlayMappingContext, 0);
		}
	}
}

void AMergeTownPawn::RemoveGameplayMappingContext()
{
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->RemoveMappingContext(GamePlayMappingContext);
		}
	}
}

// SWIPE CONTROLLS

void AMergeTownPawn::TouchPressed(ETouchIndex::Type FingerIndex, FVector Location)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("TouchPressed"));
	UE_LOG(LogTemp, Log, TEXT("TouchPressed"));
	TouchPressedLocation = FVector2D(Location);
}

void AMergeTownPawn::TouchReleased(ETouchIndex::Type FingerIndex, FVector Location)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("TouchReleased"));
	UE_LOG(LogTemp, Log, TEXT("TouchReleased"));
	isSwipe = false;
}

void AMergeTownPawn::TouchMoved(ETouchIndex::Type FingerIndex, FVector Location)
{
	FVector2D TouchDelta = FVector2D(Location) - TouchPressedLocation;

	float AbsX = FMath::Abs(TouchDelta.X);
	float AbsY = FMath::Abs(TouchDelta.Y);

	float ThresholdDistance = TouchDelta.Size();

	if (ThresholdDistance > MinSwipeDistance && !isSwipe) {
		if (AbsX >= AbsY) {
			if (TouchDelta.X > 0) {
				SwipeRight();
			}
			else {
				SwipeLeft();
			}
		}
		else {
			if (TouchDelta.Y < 0) {
				SwipeUp();
			}
			else {
				SwipeDown();
			}
		}
	}
}

/*
 * Mobile Swipe
*/
void AMergeTownPawn::SwipeUp()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("SwipeUp"));
	UE_LOG(LogTemp, Log, TEXT("SwipeUp"));
	isSwipe = true;
}

void AMergeTownPawn::SwipeDown()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("SwipeDown"));
	UE_LOG(LogTemp, Log, TEXT("SwipeDown"));
	isSwipe = true;
}

void AMergeTownPawn::SwipeLeft()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("SwipeLeft"));
	UE_LOG(LogTemp, Log, TEXT("SwipeLeft"));
	isSwipe = true;
}

void AMergeTownPawn::SwipeRight()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("SwipeRight"));
	UE_LOG(LogTemp, Log, TEXT("SwipeRight"));
	isSwipe = true;
}