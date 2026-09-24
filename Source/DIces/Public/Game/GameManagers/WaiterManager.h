

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WaiterManager.generated.h"


DECLARE_DELEGATE(FWaiterCall);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DICES_API UWaiterManager : public UActorComponent
{
	GENERATED_BODY()

public:	

	UWaiterManager();
	
	FWaiterCall WaiterCall;
	UFUNCTION()
	void RandWaiterServe() const;
	UFUNCTION()
	void WaiterServe() const;
	
protected:

	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere)
	int ServeChance = 0;

public:	

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
