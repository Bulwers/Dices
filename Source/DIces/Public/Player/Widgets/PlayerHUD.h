

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "PlayerHUD.generated.h"

DECLARE_MULTICAST_DELEGATE(FEndTurnDelegate);
DECLARE_DELEGATE(FDismissDelegate);

UCLASS()
class DICES_API UPlayerHUD : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;

	FEndTurnDelegate EndTurnDelegate;
	FDismissDelegate DismissDelegate;
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UButton* EndTurnButton;
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UButton* DismissButton;
	
	UPROPERTY(BlueprintReadOnly)
	class AGameStateBaseClass* GameState;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class ABasePlayer* Player;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class AWaiter* Waiter;
	
	UFUNCTION(BlueprintCallable)
	void EndTurn() { EndTurnDelegate.Broadcast(); };

	UFUNCTION(BlueprintCallable)
	void WaiterDismissButton() { DismissDelegate.ExecuteIfBound(); };

};
