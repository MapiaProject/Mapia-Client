// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Define.h"
#include "generated/account/Protocol.gen.hpp"
#include "generated/mmo/ClientPacketHandler.gen.hpp"
#include "net/Socket.hpp"
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

#define GetBPClass(ValueName,BPName,ClassType) static ConstructorHelpers::FClassFinder<ClassType> BP(TEXT("/Script/Engine.Blueprint'/Game/Blueprints/GameActor/BPName.BPName_C'"));\
if (BP.Succeeded())\
{\
	ValueName = BP.Class;\
}

#define BIND_MONSTER(MonsterBPName, MonsterTypeName)

class UNetwork;
class UUISystem;
class UNetObjectManager;
class UWidget;

/**
 *
 */
UCLASS()
class WOS_API UManager : public UGameInstance
{
	GENERATED_BODY()
	using SessionFactoryFunc = TFunction<TSharedPtr<class FSession>(TSharedPtr<net::Socket>)>;
public:
	UManager();
	virtual ~UManager() override;
public:
	void ConnectToServer(ServerType Type, SessionFactoryFunc SessionFactory) const;
	void HandlePacket() const;
public:
	void HandleLogin(gen::account::LoginRes* Packet) const;
	void HandleRegister(gen::account::RegisterRes* Packet);

	void HandleEnterGame(gen::mmo::EnterGameRes* Packet);
	void HandleSpawn(gen::mmo::Spawn* Packet);
	void HandleEnterMap(gen::mmo::EnterMapRes* Packet);
	void HandleLeaveMap(gen::mmo::LeaveMap* Packet);

	void HandleSpawnMonster(gen::mmo::SpawnMonster* Packet);

public:
	static TObjectPtr<UNetwork> Net(const UWorld* World = GEngine->GameViewport->GetWorld());
	static TObjectPtr<UUISystem> UI(const UWorld* World = GEngine->GameViewport->GetWorld());
	static TObjectPtr<UNetObjectManager> Object(const UWorld* World = GEngine->GameViewport->GetWorld());

	static UManager* Get(const UWorld* World = GEngine->GameViewport->GetWorld());
	void Initialize();
private:
	UPROPERTY(EditAnywhere) TSubclassOf<UNetwork> NetworkClass;
	UPROPERTY(EditAnywhere) TSubclassOf<UUISystem> UISystemClass;
	UPROPERTY(EditAnywhere) TSubclassOf<UNetObjectManager> NetObjectManagerClass;
	UPROPERTY() TObjectPtr<UNetwork> NetworkObject;
	UPROPERTY() TObjectPtr<UUISystem> UISystemObject;
	UPROPERTY() TObjectPtr<UNetObjectManager> NetObjectManagerObject;
};
