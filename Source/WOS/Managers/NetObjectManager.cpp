// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/NetObjectManager.h"
#include "GameFramework/Character.h"
#include "GameActor/PlayerCharacter.h"
#include "MonsterBindingData.h"
#include "Kismet/GameplayStatics.h"
#include <UObject/ConstructorHelpers.h>
#include <Util/NetUtility.h>

#define GetBPClass(ValueName,BPName,ClassType) static ConstructorHelpers::FClassFinder<ClassType> BPName##_BPObject(TEXT("/Script/Engine.Blueprint'/Game/Blueprints/GameActor/"#BPName"."#BPName"_C'"));\
if (BPName##_BPObject.Succeeded())\
{\
	ValueName = BPName##_BPObject.Class;\
}

UNetObjectManager::UNetObjectManager()
{
	GetBPClass(PlayerClass, BP_PlayerCharacter, ACharacter)
	GetBPClass(LocalPlayerClass, BP_LocalPlayerCharacter, ACharacter)

	static ConstructorHelpers::FObjectFinder<UMonsterBindingData> DataAsset(TEXT("/Script/WOS.MonsterBindingData'/Game/DataAssets/MonsterBindingData.MonsterBindingData'"));
	if (DataAsset.Succeeded())
	{
		MonsterActors = DataAsset.Object->MonsterActors;
	}
}

void UNetObjectManager::HandleSpawnPlayer(gen::mmo::Spawn* Packet) {
	auto* World = GetWorld();
	auto Rotation = FRotator(0, 0, 0);
	APlayerCharacter* Player = nullptr;

	if (Packet->isMine) {
		FVector Position = NetUtility::MakeVector(Packet->players[0].objectInfo.position) * 100;
		auto* Actor = World->SpawnActor(LocalPlayerClass, &Position, &Rotation);

		Player = Cast<APlayerCharacter>(Actor);
		Player->ObjectId = Packet->players[0].objectInfo.objectId;

		auto Controller = UGameplayStatics::GetPlayerController(World, 0);
		Player->Controller = Controller;
		Controller->Possess(Player);

		NetObjects.Add(Packet->players[0].objectInfo.objectId, Player);
		Player->SetName(Packet->players[0].name);
		Player->SetIsmine();
	}
	else {
		for (auto PlayerInfo : Packet->players) {
			FVector Position = NetUtility::MakeVector(PlayerInfo.objectInfo.position) * 100;

			auto* Actor = World->SpawnActor(PlayerClass, &Position, &Rotation);
			Player = Cast<APlayerCharacter>(Actor);
			Player->ObjectId = PlayerInfo.objectInfo.objectId;

			NetObjects.Add(PlayerInfo.objectInfo.objectId, Player);
			Player->SetName(PlayerInfo.name);
		}
	}
}

void UNetObjectManager::HandleLeaveMap(gen::mmo::NotifyLeaveMap* Packet)
{
	NetObjects[Packet->objectId]->DestroyNetObject();
}

void UNetObjectManager::HandleSpawnMonster(gen::mmo::SpawnMonster* Packet)
{
	int MonsterTypeIndex = (int)Packet->monsterType;
	auto* World = GetWorld();

	for (auto MonsterInfo : Packet->monsterInfos) {
		FVector Position = NetUtility::MakeVector(MonsterInfo.position);
		auto Rotation = FRotator(0, 0, 0);

		if (MonsterTypeIndex < MonsterActors.Num()) {
			auto* Actor = World->SpawnActor(MonsterActors[MonsterTypeIndex], &Position, &Rotation);
			auto Monster = reinterpret_cast<NetObject*>(Actor);

			if (Monster) {
				Monster->ObjectId = MonsterInfo.objectId;
			}
			else {
				UE_LOG(LogTemp, Warning, TEXT("Spawned monster is not NetObject"));
			}
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("To much monster asset"));
		}
	}
}

void UNetObjectManager::HandleNetObjectPacket(uint64 ObjectId, const Packet* RecievedPacket) {
	if (NetObjects.Contains(ObjectId)) {
		NetObjects[ObjectId]->RecievePacket(RecievedPacket);
	}
}