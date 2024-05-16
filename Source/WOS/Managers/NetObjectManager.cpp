// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/NetObjectManager.h"
#include "GameFramework/Character.h"
#include "GameActor/LocalPlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include <UObject/ConstructorHelpers.h>

UNetObjectManager::UNetObjectManager()
{
	static ConstructorHelpers::FClassFinder<ACharacter> LocalPlayerBP(TEXT("/Script/Engine.Blueprint'/Game/Blueprints/GameActor/BP_LocalPlayerCharacter.BP_LocalPlayerCharacter_C'"));
	if (LocalPlayerBP.Succeeded())
	{
		LocalPlayerClass = LocalPlayerBP.Class;
	}
	static ConstructorHelpers::FClassFinder<ACharacter> PlayerBP(TEXT("/Script/Engine.Blueprint'/Game/Blueprints/GameActor/BP_PlayerCharacter.BP_PlayerCharacter_C'"));
	if (PlayerBP.Succeeded())
	{
		PlayerClass = PlayerBP.Class;
	}
}

void UNetObjectManager::HandleSpawnPlayer(uint64 ObjectId, FVector Position, FString Name, bool bIsMine) {
	auto* World = GetWorld();
	auto Rotation = FRotator(0, 0, 0);
	APlayerCharacter* Player = nullptr;

	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Emerald, FString::Printf(TEXT("(%f, %f)"), Position.X, Position.Z));

	Position *= 100;


	if (bIsMine) {

		auto* Actor = World->SpawnActor(LocalPlayerClass, &Position, &Rotation);

		Player = Cast<ALocalPlayerCharacter>(Actor);

		auto Controller = UGameplayStatics::GetPlayerController(World, 0);
		Player->Controller = Controller;
		Controller->Possess(Player);
	}
	else {
		auto* Actor = World->SpawnActor(PlayerClass, &Position, &Rotation);
		Player = Cast<APlayerCharacter>(Actor);
	}
	Player->SetName(Name);
	NetObjects[ObjectId] = Player;
	Player->NetObjectId = ObjectId;
}

void UNetObjectManager::HandleNetObjectPacket(uint64 ObjectId, const Packet* RecievedPacket) {
	if (NetObjects.contains(ObjectId)) {
		NetObjects[ObjectId]->RecievePacket(RecievedPacket);
	}
}