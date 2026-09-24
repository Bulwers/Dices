

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Player/Conditions/BaseCondition.h"
#include "BaseDrink.generated.h"

class ABasePlayer;
DECLARE_DELEGATE(FDrinkTaken);

UCLASS()
class DICES_API ABaseDrink : public AActor
{
	GENERATED_BODY()
	
public:	

	ABaseDrink();
	
	FDrinkTaken DrinkTaken;

	UFUNCTION()
	virtual void Drink();
	UFUNCTION()
	void AddToPlayer(AActor* ActorClicked, FKey InKey);

	UPROPERTY(EditAnywhere)
	bool bIsPlayer = false;
	
	UFUNCTION()
	void SetCanBeClicked() { bCanBeClicked = true; }

protected:

	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<ABasePlayer> Player;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent> BottleBase;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Drink")
	int32 GoldPrice;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Drink")
	TSubclassOf<UBaseCondition> ConditionToApply;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Drink")
	int32 ConditionLifetime;
	
	UPROPERTY(EditAnywhere)
	bool bCanBeClicked = false;
	
	UPROPERTY()
	int32 PlayerDrinkSlot = INDEX_NONE;
	
public:	

};
