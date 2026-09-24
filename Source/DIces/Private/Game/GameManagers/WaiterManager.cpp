// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/GameManagers/WaiterManager.h"

// Sets default values for this component's properties
UWaiterManager::UWaiterManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}

// Called when the game starts
void UWaiterManager::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void UWaiterManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

// Random chance for waiter to serve during the game
void UWaiterManager::RandWaiterServe() const
{
	if (FMath::RandRange(0, 100) <= ServeChance)
	{
		WaiterCall.ExecuteIfBound();
		UE_LOG(LogTemp, Warning, TEXT("Random Waiter Call"));
	}
}

// Serving waiter when called
void UWaiterManager::WaiterServe() const
{
	WaiterCall.ExecuteIfBound();
	UE_LOG(LogTemp, Warning, TEXT("Waiter Call"));
}
