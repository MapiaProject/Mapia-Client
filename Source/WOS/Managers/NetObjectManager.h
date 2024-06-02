// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Managers/ManagerBase.h"
#include "Managers/Network.h"
#include "generated/mmo/Struct.gen.hpp"
#include "generated/mmo/Protocol.gen.hpp"
#include "GameActor/NetObject.h"
#include "NetObjectManager.generated.h"

/**
 *
 */
UCLASS()
class WOS_API UNetObjectManager : public UManagerBase
{
	GENERATED_BODY()

public:
	UNetObjectManager();
	void HandleNetObjectPacket(uint64 ObjectId, const Packet* RecievedPacket);
	void RequestEnterMap(FString MapName);
	FString GetCurrentMapName();
	TArray<TArray<int>>* GetCurrentMapData();

	void HandleEnterMap(gen::mmo::EnterMapRes* Packet);
	void HandleSpawnPlayer(gen::mmo::Spawn* Packet);
	void HandleLeaveMap(gen::mmo::NotifyLeaveMap* Packet);
	void HandleSpawnMonster(gen::mmo::SpawnMonster* Packet);
private:
	TMap<uint64, NetObject*> NetObjects;
	TSubclassOf<ACharacter> PlayerClass;
	TSubclassOf<ACharacter> LocalPlayerClass;
	TArray<TSubclassOf<AActor>> MonsterActors;

	FString CurrentMapName;
	FString LastRequstMapName;
	TArray<TArray<int>> CurrentMapData;
};