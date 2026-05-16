// Fill out your copyright notice in the Description page of Project Settings.


#include "Misc/Items/Chopper.h"
#include "Player/BasePlayer.h"
#include "Enemies/BaseEnemy.h"
#include "Kismet/GameplayStatics.h"
#include "Game/GameStateBaseClass.h"


// Sets default values
AChopper::AChopper()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AChopper::BeginPlay()
{
	Super::BeginPlay();
	
	GameState = Cast<AGameStateBaseClass>(UGameplayStatics::GetGameState(GetWorld()));
	PlayerCharacter = Cast<ABasePlayer>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
}

// Called every frame
void AChopper::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!EnemyCharacter)
	{
		EnemyCharacter = GameState->GetEnemy();
	}
}

void AChopper::ChopperHit(int DicesToRemove)
{
	PlayerCharacter->PlayerDicesOnTable[DicesToRemove]->DiceMesh->SetVisibility(false);
	PlayerCharacter->PlayerDicesOnTable[DicesToRemove]->bIsVisible = false;
	UE_LOG(LogTemp, Warning, TEXT("Chopper Hit Execute Player"));
	EnemyCharacter->EnemyDicesOnTable[DicesToRemove]->DiceMesh->SetVisibility(false);
	EnemyCharacter->EnemyDicesOnTable[DicesToRemove]->bIsVisible = false;
	UE_LOG(LogTemp, Warning, TEXT("Chopper Hit Execute Enemy"));
}