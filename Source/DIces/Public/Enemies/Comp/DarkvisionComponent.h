

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DarkvisionComponent.generated.h"

class ABaseDice;
class ADicePlayerController;
class UPlayerHUD;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DICES_API UDarkvisionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	UDarkvisionComponent();
	
	UFUNCTION(BlueprintCallable)
	void LightsOut();
	
	UFUNCTION(BlueprintCallable)
	void SwapDices(
		UPARAM(ref) TArray<ABaseDice*>& EnemyDicesOnTable, 
		const TArray<ABaseDice*>& PlayerDicesOnTable, 
		const TArray<FVector>& Spots);
	UFUNCTION(BlueprintCallable)
	void SwapbCanSwapDices() { bIsCandleExtinguished = !bIsCandleExtinguished; }
	
protected:
	
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Candle")
	class ACandleClass* CandleRef;
	UPROPERTY()
	ADicePlayerController* PlayerController;
	UPROPERTY()
	UPlayerHUD* PlayerHUD;
	
	UPROPERTY(VisibleAnywhere, Category= "Candle")
	bool bIsCandleExtinguished = false;
	UFUNCTION()
	void InitCandleRef();
	UPROPERTY(VisibleAnywhere, Category= "Candle")
	bool bIsSwapped = false;
	
	UFUNCTION()
	void EndTurn() { bIsSwapped = false; }

public:	
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
};
