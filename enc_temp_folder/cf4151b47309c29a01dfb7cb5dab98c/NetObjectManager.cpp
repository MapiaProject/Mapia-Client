// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/NetObjectManager.h"
#include "GameFramework/Character.h"
#include "GameActor/LocalPlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

void UNetObjectManager::HandleSpawnPlayer(uint64 ObjectId, FVector Position, FString Name, bool bIsMine) {
	auto* World = GetWorld();
	auto Rotation = FRotator(0, 0, 0);
	APlayerCharacter* Player;
	if (bIsMine) {
		auto PlayerBP = LoadObject<UBlueprint>(NULL, TEXT("/Engine/EngineMaterials/DefaultWhiteGrid.DefaultWhiteGrid"), NULL, LOAD_None, NULL);
		auto* Actor = World->SpawnActor(PlayerBP->StaticClass(), &Position, &Rotation);
		Player = Cast<ALocalPlayerCharacter>(Actor);

		auto Controller = UGameplayStatics::GetPlayerController(World, 0);
		Player->Controller = Controller;
	}
	else {
		auto* Actor = World->SpawnActor(APlayerCharacter::StaticClass(), &Position, &Rotation);
		Player = Cast<APlayerCharacter>(Actor);
	}
	Player->SetName(Name);
	NetObjects[ObjectId] = Player;
}

void UNetObjectManager::HandleNetObjectPacket(uint64 ObjectId, const Packet* RecievedPacket) {
	if (NetObjects.contains(ObjectId)) {
		NetObjects[ObjectId]->RecievePacket(RecievedPacket);
	}
}