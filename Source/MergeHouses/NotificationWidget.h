// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NotificationWidget.generated.h"

/**
 * 
 */
UCLASS()
class MERGEHOUSES_API UNotificationWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// Text parameter for notification text
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Notification")
	FString NotificationText;

	// Close method to remove the widget
	UFUNCTION(BlueprintCallable, Category = "Notification")
	void CloseNotification();

	void SetNotificationText(const FString& InNotificationText);
};
