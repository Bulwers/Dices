

#include "Misc/CandleClass.h"

ACandleClass::ACandleClass()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ACandleClass::BeginPlay()
{
	Super::BeginPlay();
	LightCandle();
}

void ACandleClass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}