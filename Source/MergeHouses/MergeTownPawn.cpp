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

// Sets default values
AMergeTownPawn::AMergeTownPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->SetUsingAbsoluteRotation(true);
	SpringArm->SetUsingAbsoluteLocation(true);
	SpringArm->TargetArmLength = 500.f;
	SpringArm->SetRelativeLocation(FVector(0.f, 0.f, 350.f));
	SpringArm->SetRelativeRotation(FRotator(-30.f, -120.f, 0.f));
	SpringArm->bDoCollisionTest = false;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	Camera->bUsePawnControlRotation = false;
}

void AMergeTownPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Started, this, &AMergeTownPawn::MakeMove);
	}
}

// Called when the game starts or when spawned
void AMergeTownPawn::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(GamePlayMappingContext, 0);
		}
	}

	if (MenuSignReference)
	{
		SetActorLocation(MenuSignReference->GetActorLocation());
	}
}

// Called every frame
void AMergeTownPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsMovingToTarget)
	{
		FVector CurrentLocation = GetActorLocation();
		FVector Direction = (TargetLocation - CurrentLocation).GetSafeNormal();	
		FVector NewLocation = CurrentLocation + Direction * PawnMovingSpeed * DeltaTime;
		SetActorLocation(NewLocation);

		FRotator CurrentRotation = SpringArm->GetComponentRotation();
		FRotator NewRotation = FMath::RInterpTo(CurrentRotation, SpringArmRotation, DeltaTime, RotationSpeed);
		SpringArm->SetRelativeRotation(NewRotation);

		FVector CurrentOffset = SpringArm->GetRelativeLocation();
		FVector OffsetDirection = (SpringArmOffset - CurrentOffset).GetSafeNormal();
		FVector NewOffset = CurrentOffset + OffsetDirection * SpringArmMovingSpeed * DeltaTime;
		SpringArm->SetRelativeLocation(NewOffset);

		// Update Spring Arm Length
		float CurrentArmLength = SpringArm->TargetArmLength;
		float NewArmLength = FMath::Lerp(CurrentArmLength, SpringArmLength, DeltaTime * SpringArmLengthSpeed);
		SpringArm->TargetArmLength = NewArmLength;

		// Check for completion
		bool bReachedLocation = FVector::DistSquared(NewLocation, TargetLocation) < FMath::Square(10.f);
		bool bReachedRotation = FMath::IsNearlyEqual(CurrentRotation.Pitch, SpringArmRotation.Pitch, 0.1f) &&
			FMath::IsNearlyEqual(CurrentRotation.Yaw, SpringArmRotation.Yaw, 0.1f) &&
			FMath::IsNearlyEqual(CurrentRotation.Roll, SpringArmRotation.Roll, 0.1f);
		bool bReachedArmLength = FMath::IsNearlyEqual(CurrentArmLength, SpringArmLength, 0.1f);

		if (bReachedLocation && bReachedRotation && bReachedArmLength)
		{
			bIsMovingToTarget = false;
			SetActorLocation(TargetLocation);
			SpringArm->SetRelativeRotation(SpringArmRotation);
			SpringArm->SetRelativeLocation(SpringArmOffset);
			SpringArm->TargetArmLength = SpringArmLength;
		}
	}
}

void AMergeTownPawn::MakeMove(const FInputActionValue& Value)
{
	FVector2D MoveValue = Value.Get<FVector2D>();

	if (GameBoardReference)
	{
		GameBoardReference->MakeMove(MoveValue.X, MoveValue.Y);
	}
}

void AMergeTownPawn::MoveToBoard(FVector NewTargetLocation)
{
	TargetLocation = NewTargetLocation;
	SpringArmRotation = FRotator(-55.f, -60.f, 0.f);
	SpringArmOffset = FVector(40.f, 315.f, 150.f);
	SpringArmLength = 250.f;
	bIsMovingToTarget = true;
}

void AMergeTownPawn::SetGameBoardReference(AGameBoard* GameBoard)
{
	GameBoardReference = GameBoard;
}

void AMergeTownPawn::SetMenuSignReference(AMenuSign* MenuSign)
{
	MenuSignReference = MenuSign;
}
