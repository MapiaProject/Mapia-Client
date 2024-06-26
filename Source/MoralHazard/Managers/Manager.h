// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <optional>

#include "CoreMinimal.h"
#include "Managers/Network.h"
#include "Network/generated/Protocol.gen.hpp"

#include "Manager.generated.h"

#define INIT_MANAGER(name)\
if (!name##Object)												\
{																\
	if (name##Class->StaticClass())								\
	{															\
		name##Object = NewObject<U##name>(this, name##Class);	\
	}															\
	else														\
	{															\
		name##Object = name##Class.GetDefaultObject();			\
	}															\
}																\

/**
 * 
 */
UCLASS()
class MORALHAZARD_API UManager : public UGameInstance
{
	GENERATED_BODY()
public:
	UManager();
	virtual ~UManager() override;
public:
	void ConnectToServer() const;
	void HandlePacket() const;
	void DisconnectFromServer() const;
	void EnterRoom(uint32 Id);
	void LeaveRoom();

	void RefreshRoom(gen::NotifyRoomList RoomList);
	void HandleRoomEventResult(gen::RoomEventRes EventRes);
public:
	static TObjectPtr<UNetwork> Net(const UWorld* World = GEngine->GameViewport->GetWorld());
	static UManager* Instance(const UWorld* World = GEngine->GameViewport->GetWorld());
	void Initialize();
private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UNetwork> NetworkClass;
	UPROPERTY()
	TObjectPtr<UNetwork> NetworkObject;

	std::optional<uint32> CurrentRoomId;
};	
