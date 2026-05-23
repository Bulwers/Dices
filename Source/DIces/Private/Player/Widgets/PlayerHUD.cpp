

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

	if (GameState) EndTurnDelegate.AddUObject(GameState->GetBrawlManager(), &UBrawlManager::EndTurn);
	if (Waiter) DismissDelegate.BindUObject(Waiter, &AWaiter::SetStartingLocAndRot);
}
