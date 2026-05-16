

#include "Player/Widgets/DrinkBuffWidget.h"
#include "Player/BasePlayer.h"
#include "Player/Conditions/BaseCondition.h"
#include "Kismet/GameplayStatics.h"
#include "Player/Comp/PlayerCameraManagerComponent.h"
#include "Components/CanvasPanelSlot.h"

void UDrinkBuffWidget::NativeConstruct()
{
    Super::NativeConstruct();

    Player = Cast<ABasePlayer>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
    
    if (Player)
    {
        Player->CameraComp->OnCameraTop.AddDynamic(this, &UDrinkBuffWidget::OnCameraTop);
        Player->CameraComp->OnCameraBottom.AddDynamic(this, &UDrinkBuffWidget::OnCameraBottom);
        Player->CameraComp->OnCameraLeft.AddDynamic(this, &UDrinkBuffWidget::OnCameraLeft);
        Player->CameraComp->OnCameraRight.AddDynamic(this, &UDrinkBuffWidget::OnCameraRight);
        Player->CameraComp->OnCameraWaiter.AddDynamic(this, &UDrinkBuffWidget::OnCameraWaiter);
    }
    
    HideButtons();
}

void UDrinkBuffWidget::OnCameraTop()
{
    HideButtons();
    for (const UBaseCondition* Condition : Player->DrinkConditions)
    {
        if (Condition && Condition->ComponentTags.Contains(FName("DiceBuff")))
        {
            PlusButton->SetVisibility(ESlateVisibility::Visible);
            break;
        }
    }
}

void UDrinkBuffWidget::OnCameraBottom()
{
    HideButtons();
}

void UDrinkBuffWidget::OnCameraLeft()
{
    HideButtons();
}

void UDrinkBuffWidget::OnCameraRight()
{
    HideButtons();
    for (const UBaseCondition* Condition : Player->DrinkConditions)
    {
        if (Condition && Condition->ComponentTags.Contains(FName("Lucky")))
        {
            RerollButton->SetVisibility(ESlateVisibility::Visible);
            break;
        }
    }
}

void UDrinkBuffWidget::OnCameraWaiter()
{
    HideButtons();
}

void UDrinkBuffWidget::HideButtons()
{
    if (RerollButton && RerollButton->IsVisible())
        RerollButton->SetVisibility(ESlateVisibility::Hidden);
    if (PlusButton && PlusButton->IsVisible())
        PlusButton->SetVisibility(ESlateVisibility::Hidden);
    if (PlusOneButton && PlusOneButton->IsVisible())
        PlusOneButton->SetVisibility(ESlateVisibility::Hidden);
    if (PlusTwoButton && PlusTwoButton->IsVisible())
        PlusTwoButton->SetVisibility(ESlateVisibility::Hidden);
}

void UDrinkBuffWidget::RerollDices()
{
    for (UBaseCondition* Condition : Player->DrinkConditions)
    {
        if (Condition && Condition->ComponentTags.Contains(FName("Lucky")))
        {
            Condition->DrinkEffect();
            break;
        }
    }
}

void UDrinkBuffWidget::PlusBuffButtons()
{
    bCanBuffButton = true;
    
    UCanvasPanelSlot* PlusOneButtonSlot = Cast<UCanvasPanelSlot>(PlusOneButton->Slot);
    UCanvasPanelSlot* PlusTwoButtonSlot = Cast<UCanvasPanelSlot>(PlusTwoButton->Slot);
    
    if (HasPlusOneDrinkCondition())
    {
        PlusOneButton->SetVisibility(ESlateVisibility::Visible);
        
        if (HasPlusTwoDrinkCondition())
        {
            PlusTwoButton->SetVisibility(ESlateVisibility::Visible);
            if  (PlusOneButtonSlot) PlusOneButtonSlot->SetPosition(FirstBuffButtonPosition);
            if  (PlusTwoButtonSlot) PlusTwoButtonSlot->SetPosition(SecondBuffButtonPosition);
        }
        else
        {
            PlusTwoButton->SetVisibility(ESlateVisibility::Hidden);
            if (PlusOneButtonSlot) PlusOneButtonSlot->SetPosition(SoloBuffButtonPosition);
        }
    }
    else
    {
        PlusOneButton->SetVisibility(ESlateVisibility::Hidden);
        
        if (HasPlusTwoDrinkCondition())
        {
            PlusTwoButton->SetVisibility(ESlateVisibility::Visible);
            if  (PlusTwoButtonSlot) PlusTwoButtonSlot->SetPosition(SoloBuffButtonPosition);
        }
        else
        {
            PlusTwoButton->SetVisibility(ESlateVisibility::Hidden);
        }
    }
}

bool UDrinkBuffWidget::HasPlusOneDrinkCondition()
{
    for (const UBaseCondition* Condition : Player->DrinkConditions)
    {
        if (Condition && Condition->ComponentTags.Contains(FName ("PlusOne")) && Condition->bCanBuff == true)
        {
            return true;
        }
    }
    return false;
}

void UDrinkBuffWidget::PlusOneBuff()
{
    Player->bPlusOneBuff = true;
    Player->bPlusTwoBuff = false;
}

bool UDrinkBuffWidget::HasPlusTwoDrinkCondition()
{
    for (const UBaseCondition* Condition : Player->DrinkConditions)
    {
        if (Condition && Condition->ComponentTags.Contains(FName ("PlusTwo")) && Condition->bCanBuff == true)
        {
            return true;
        }
    }
    return false;
}

void UDrinkBuffWidget::PlusTwoBuff()
{
    Player->bPlusTwoBuff = true;
    Player->bPlusOneBuff = false;
}