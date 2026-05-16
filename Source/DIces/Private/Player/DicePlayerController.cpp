// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/DicePlayerController.h"

ADicePlayerController::ADicePlayerController()
{
	bReplicates = true;
}

void ADicePlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (PlayerHUDWidgetToSpawn)
	{
		PlayerWidget = CreateWidget<UUserWidget>(this, PlayerHUDWidgetToSpawn);
		if (PlayerWidget)
		{
			PlayerWidget->AddToViewport();
		}
	}
	if (DrinkBuffWidgetToSpawn)
	{
		BuffWidget = CreateWidget<UUserWidget>(this, DrinkBuffWidgetToSpawn);
		if (BuffWidget)
		{
			BuffWidget->AddToViewport();
		}
	}
}