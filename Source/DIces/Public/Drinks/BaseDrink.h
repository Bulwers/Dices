

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
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

	UPROPERTY(VisibleAnywhere)
	bool bIsPlayer;
	
	UFUNCTION()
	void SetCanBeClicked() { bCanBeClicked = true; }

protected:

	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	ABasePlayer* Player;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* BottleBase;
	
	UPROPERTY(EditAnywhere)
	int GoldPrice;
	
	UPROPERTY()
	bool bCanBeClicked = false;
	
public:	

	virtual void Tick(float DeltaTime) override;

};
