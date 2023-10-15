// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MergeTownPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class MERGEHOUSES_API AMergeTownPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = Camera)
		float CameraBlendSpeed = 1.f;

	AMergeTownPlayerController();

	virtual void BeginPlay() override;

	void SetMenuCameraActive();
	void SetBoardCameraActive();
};
