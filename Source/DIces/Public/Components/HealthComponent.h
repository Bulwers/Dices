
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DELEGATE(FOnDeathEffects);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DICES_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UHealthComponent();

	UFUNCTION()
	void GetHit();

	UFUNCTION()
	int32 GetHealth() const { return Health; }

	FOnDeathEffects OnDeathEffects;

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere)
	int32 MaxHealth = 4;
	UPROPERTY(VisibleAnywhere)
	int32 Health;

public:	
		
};
