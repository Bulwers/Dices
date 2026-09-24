

#include "Components/HealthComponent.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;
}

void UHealthComponent::GetHit()
{
	if (Health <= 0)
	{
		return;
	}
	Health -= 1;
	if (Health <= 0)
	{
		OnDeathEffects.ExecuteIfBound();
	}
}


