// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Managers/ManagerBase.h"
#include "DataClass/MapData.h"
#include "../Network/generated/mmo/Enum.gen.hpp"
#include "../Network/generated/mmo/Struct.gen.hpp"
#include "NetObjectManager.generated.h"

namespace gen::mmo
{
	class NotifySpawn;
	class NotifyLeaveMap;
	class Spawn;
	class EnterMapRes;
}

class Packet;
class NetObject;

class ObjectInfo {
public:
	ObjectInfo(); 
	ObjectInfo(gen::mmo::ObjectInfo* Origin);
	~ObjectInfo();

	uint64 objectId;
	Vector2Int position;
	gen::mmo::EObjectType type;
	uint32 remainHp;
	FString name;
};

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
	MapData* GetCurrentMapData();

	void HandleEnterMap(gen::mmo::EnterMapRes* Packet);
	void HandleSpawnPlayer(gen::mmo::Spawn* Packet);
	void HandleLeaveMap(gen::mmo::NotifyLeaveMap* Packet);
	void HandleNotifySpawn(gen::mmo::NotifySpawn* Packet);
	void NotifySpawnLogic(ObjectInfo* Object);

	NetObject* GetObjectById(uint64 Id);
private:
	TMap<uint64, NetObject*> NetObjects;
	TSubclassOf<ACharacter> PlayerClass;
	TSubclassOf<ACharacter> LocalPlayerClass;
	TArray<TSubclassOf<AActor>> MonsterActors;

	TQueue<ObjectInfo> NotifySpawnBuffer;

	FString LastRequstMapName;
	MapData CurrentMapData;

	bool ChangingMap;
};