

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "DrinkBuffWidget.generated.h"

UCLASS()
class DICES_API UDrinkBuffWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	
	virtual void NativeConstruct() override;
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UButton* RerollButton;
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UButton* PlusButton;
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UButton* PlusOneButton;
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UButton* PlusTwoButton;
	
	UFUNCTION()
	void HideButtons();
	
	UPROPERTY(EditDefaultsOnly)
	FVector2D SoloBuffButtonPosition;
	UPROPERTY(EditDefaultsOnly)
	FVector2D FirstBuffButtonPosition;
	UPROPERTY(EditDefaultsOnly)
	FVector2D SecondBuffButtonPosition;
	
	UFUNCTION()
	void OnCameraTop();
	UFUNCTION()
	void OnCameraBottom();
	UFUNCTION()
	void OnCameraLeft();
	UFUNCTION()
	void OnCameraRight();
	UFUNCTION()
	void OnCameraWaiter();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class ABasePlayer* Player;
	
	UFUNCTION(BlueprintCallable)
	void RerollDices();
	
	UFUNCTION(BlueprintCallable)
	void PlusBuffButtons();
	UPROPERTY(BlueprintReadWrite)
	bool bCanBuffButton;

	UFUNCTION(BlueprintCallable)
	bool HasPlusOneDrinkCondition();
	UFUNCTION(BlueprintCallable)
	void PlusOneBuff();

	UFUNCTION(BlueprintCallable)
	bool HasPlusTwoDrinkCondition();
	UFUNCTION(BlueprintCallable)
	void PlusTwoBuff();
};
