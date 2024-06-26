// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/NetObjectManager.h"
#include "GameFramework/Character.h"
#include "GameActor/Player/PlayerCharacter.h"
#include "DataClass/MonsterBindingData.h"
#include "Util/Ini.h"
#include "Manager.h"
#include "Kismet/GameplayStatics.h"
#include <UObject/ConstructorHelpers.h>
#include <Util/NetUtility.h>

#include "Network.h"

#ifdef GetBPClass
#undef GetBPClass
#endif
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

void UNetObjectManager::HandleEnterMap(gen::mmo::EnterMapRes* Packet)
{
	if (Packet->success)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Emerald, TEXT("Enter map success"));

		FString path = FPaths::ProjectDir() + TEXT("Source\\WOS\\Network\\generated\\mapData\\") + LastRequstMapName + TEXT(".ini");

		Ini ini = Ini(path);
		FString data = ini[TEXT("map")].Get<FString>("data");
		TArray<TArray<int>> mapData;
		int xSize, zSize;

		//맵 사이즈 추출
		FString size = ini[TEXT("info")].Get<FString>("size");
		FString xData, zData;
		size.Split(TEXT(","), &xData, &zData);
		xSize = FCString::Atoi(*xData);
		zSize = FCString::Atoi(*zData);

		//맵 배열 생성
		mapData.Reset(0);
		for (int z = 0;z < zSize;z++) {
			TArray<int> Array = TArray<int>();
			for (int x = 0;x < xSize;x++) {
				TCHAR c = data[z * xSize + x];
				Array.Add(FCString::Atoi(&c));
			}
			mapData.Insert(Array, 0);
		}

		CurrentMapData = MapData(LastRequstMapName, mapData);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("Can't enter map"));
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
		Player->HandleSpawn(Vector2Int(Packet->players[0].objectInfo.position.x, Packet->players[0].objectInfo.position.y));
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

NetObject* UNetObjectManager::GetObjectById(uint64 Id)
{
	return NetObjects[Id];
}

void UNetObjectManager::HandleNetObjectPacket(uint64 ObjectId, const Packet* RecievedPacket) {
	if (NetObjects.Contains(ObjectId)) {
		NetObjects[ObjectId]->ReceivePacket(RecievedPacket);
	}
}

void UNetObjectManager::RequestEnterMap(FString MapName)
{
	gen::mmo::EnterMapReq EnterMap;
	EnterMap.mapName = MapName;
	gen::mmo::Vector2 Pos;
	Pos.x = -1;
	Pos.y = -1;
	UManager::Net()->Send(ServerType::MMO, &EnterMap);

	LastRequstMapName = MapName;
}

MapData* UNetObjectManager::GetCurrentMapData()
{
	return &CurrentMapData;
}
