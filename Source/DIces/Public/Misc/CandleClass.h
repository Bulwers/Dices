

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CandleClass.generated.h"

DECLARE_DELEGATE(FSwitchLight)

UCLASS()
class DICES_API ACandleClass : public AActor
{
	GENERATED_BODY()
	
public:	
	ACandleClass();
	
	FSwitchLight OnLightSwitch;
	
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void OnExtinguishedLight();
	
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void OnLightedLight();
	
	UFUNCTION(blueprintCallable)
	bool IsCandleExtinguished() const { return bIsExtinguished; }
	
protected:
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintCallable)
	void ExtinguishCandle()	{ bIsExtinguished = true; OnLightSwitch.ExecuteIfBound(); }
	UFUNCTION(BlueprintCallable)
	void LightCandle() { bIsExtinguished = false; OnLightSwitch.ExecuteIfBound(); }
	
	UPROPERTY(BlueprintReadWrite)
	bool bIsExtinguished = false;

public:	
	virtual void Tick(float DeltaTime) override;

};
