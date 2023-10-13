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

	AMenuSign* FoundSign = nullptr;
	for (TActorIterator<AMenuSign> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		FoundSign = *ActorItr;
		break;
	}

	if (FoundSign)
	{
		SetActorLocation(FoundSign->GetActorLocation());
	}
}

// Called every frame
void AMergeTownPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMergeTownPawn::MakeMove(const FInputActionValue& Value)
{
	FVector2D MoveValue = Value.Get<FVector2D>();
}

