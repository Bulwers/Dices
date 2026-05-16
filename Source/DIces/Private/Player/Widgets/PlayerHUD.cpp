

#include "Player/Widgets/PlayerHUD.h"
#include "Waiter/Waiter.h"
#include "Player/BasePlayer.h"
#include "Game/GameManagers/BrawlManager.h"
#include "Game/GameStateBaseClass.h"
#include "Kismet/GameplayStatics.h"

void UPlayerHUD::NativeConstruct()
{
    Super::NativeConstruct();

    Player = Cast<ABasePlayer>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
    GameState = Cast<AGameStateBaseClass>(UGameplayStatics::GetGameState(GetWorld()));
	Waiter = Cast<AWaiter>(UGameplayStatics::GetActorOfClass(GetWorld(), AWaiter::StaticClass()));

}

void UPlayerHUD::EndTurn()
{
    GameState->GetBrawlManager()->CheckingResults();
	GameState->GetBrawlManager()->ResetSettings();
    GameState->GetBrawlManager()->ResetDicesPosition();
    GameState->GetBrawlManager()->ResetPoints();
}

void UPlayerHUD::WaiterDismissButton()
{
	Waiter->SetStartingLocAndRot();
}
