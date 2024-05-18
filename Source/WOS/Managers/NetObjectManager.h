// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Managers/ManagerBase.h"
#include "Managers/Network.h"
#include "generated/mmo/Struct.gen.hpp"
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
	void HandleSpawnPlayer(uint64 ObjectId, FVector Position, FString Name, bool bIsMine = false);
	void HandleLeaveMap(uint64 ObjectId);
	void HandleSpawnMonster(gen::mmo::ObjectInfo MonsterInfo, gen::mmo::EMonsterType MonsterType);
	void HandleNetObjectPacket(uint64 ObjectId, const Packet* RecievedPacket);
private:
	TMap<uint64, NetObject*> NetObjects;
	TSubclassOf<ACharacter> PlayerClass;
};