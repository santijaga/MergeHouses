// Fill out your copyright notice in the Description page of Project Settings.


#include "HowToPlayWidget.h"

void UHowToPlayWidget::NextPage()
{
	if (CurrentPageIndex < TotalPages - 1)
	{
		CurrentPageIndex++;
	}
}

void UHowToPlayWidget::PreviousPage()
{
	if (CurrentPageIndex > 0)
	{
		CurrentPageIndex--;
	}
}
