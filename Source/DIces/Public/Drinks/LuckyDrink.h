

#pragma once

#include "CoreMinimal.h"
#include "BaseDrink.h"
#include "LuckyDrink.generated.h"

UCLASS()
class DICES_API ALuckyDrink : public ABaseDrink
{
	GENERATED_BODY()
	
public:
	
	virtual void Drink() override;

protected:

	virtual void BeginPlay() override;

public:

	virtual void Tick(float DeltaTime) override;
};
