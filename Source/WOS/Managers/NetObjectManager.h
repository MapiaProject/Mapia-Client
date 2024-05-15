// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Managers/ManagerBase.h"
#include "GameActor/PlayerCharacter.h"
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
	void HandleNetObjectPacket(uint64 ObjectId, const Packet* RecievedPacket);
public:
	template<class T> requires std::is_base_of_v<NetObject, T>
	TArray<T> FindObjectsByType()
	{
		TArray<T> Result;
		return Result;
	}
private:
	TMap<uint64, NetObject*> NetObjects;
	TSubclassOf<ACharacter> PlayerClass;
};