// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/NetObjectManager.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

void UNetObjectManager::HandleSpawnPlayer(uint64 ObjectId, FVector Position, FString Name, bool bIsMine) {
	auto* World = GetWorld();
	auto Rotation = FRotator(0, 0, 0);
	auto* Actor = World->SpawnActor(APlayerCharacter::StaticClass(), &Position, &Rotation);
	if (Actor == nullptr) {
		UE_LOG(LogTemp, Log, TEXT("Spawned Player is null"));
	}
	else {
		auto* Player = Cast<APlayerCharacter>(Actor);
		NetObjects[ObjectId] = Player;
		Player->SetName(Name);

		if (bIsMine) {
			auto Controller = UGameplayStatics::GetPlayerController(World, 0);
			Player->Controller = Controller;
		}
	}
}

void UNetObjectManager::HandleNetObjectPacket(uint64 ObjectId, const Packet* RecievedPacket) {
	if (NetObjects.contains(ObjectId)) {
		NetObjects[ObjectId]->RecievePacket(RecievedPacket);
	}
}