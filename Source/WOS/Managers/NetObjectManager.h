// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Managers/ManagerBase.h"
#include "GameActor/PlayerCharacter.h"
#include "GameActor/NetObject.h"
#include <map>
using namespace std;
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
	void HandleNetObjectPacket(uint64 ObjectId, const Packet* RecievedPacket);
private:
	map<uint64, NetObject*> NetObjects;
	TSubclassOf<ACharacter> PlayerClass;
};
