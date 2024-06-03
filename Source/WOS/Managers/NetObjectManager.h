// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Managers/ManagerBase.h"
#include "NetObjectManager.generated.h"

namespace gen::mmo
{
	class SpawnMonster;
	class NotifyLeaveMap;
	class Spawn;
	class EnterMapRes;
}

class Packet;
class NetObject;

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

	void HandleSpawnPlayer(gen::mmo::Spawn* Packet);
	void HandleLeaveMap(gen::mmo::NotifyLeaveMap* Packet);
	void HandleSpawnMonster(gen::mmo::SpawnMonster* Packet);

	NetObject* GetObjectById(uint64 Id);
private:
	TMap<uint64, NetObject*> NetObjects;
	TSubclassOf<ACharacter> PlayerClass;
	TSubclassOf<ACharacter> LocalPlayerClass;
	TArray<TSubclassOf<AActor>> MonsterActors;
};