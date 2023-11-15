// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedStruct.h"
#include "Cell.generated.h"

/**
 * 
 */
UCLASS()
class MERGEHOUSES_API UCell : public UUserDefinedStruct
{
	GENERATED_BODY()
	
public:
	int32 Value = 0;
	int32 ModelID = 0;
};
