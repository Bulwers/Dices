

#pragma once

#include "CoreMinimal.h"
#include "BaseDrink.h"
#include "223455DiceDrink.generated.h"

UCLASS()
class DICES_API A223455DiceDrink : public ABaseDrink
{
	GENERATED_BODY()
	
public:

	virtual void Drink() override;

protected:

	virtual void BeginPlay() override;

public:

	virtual void Tick(float DeltaTime) override;
};
