// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/Widgets/PlayerHUD.h"
#include "GameFramework/PlayerController.h"
#include "DicePlayerController.generated.h"

class UBaseDrinkWidget;

UCLASS()
class DICES_API ADicePlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	ADicePlayerController();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> PlayerHUDWidgetToSpawn;
	UPROPERTY(VisibleAnywhere)
	UUserWidget* PlayerWidget;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> DrinkBuffWidgetToSpawn;
	UPROPERTY(VisibleAnywhere)
	UUserWidget* BuffWidget;

protected:

	virtual void BeginPlay() override;

};
