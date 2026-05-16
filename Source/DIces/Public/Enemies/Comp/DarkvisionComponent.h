

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DarkvisionComponent.generated.h"

class ABaseEnemy;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DICES_API UDarkvisionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	UDarkvisionComponent();
	
	UFUNCTION(BlueprintCallable)
	void LightsOut();
	
	UFUNCTION(BlueprintCallable)
	void SwapDices(ABaseEnemy* Owner);
	UFUNCTION(BlueprintCallable)
	void SwapbCanSwapDices() { bCanSwapDices = !bCanSwapDices; }
	
protected:
	
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Candle")
	class ACandleClass* CandleRef;
	UPROPERTY()
	bool bCanSwapDices = false;
	UFUNCTION()
	void InitCandleRef();

public:	
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
};
