// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Define.h"
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

namespace gen::mmo
{
	class EnterMapRes;
	class EnterGameRes;
	class NotifyChat;
}

namespace gen::account
{
	class CheckNicknameRes;
	class RegisterRes;
	class LoginRes;
}

namespace net
{
	class Socket;
}

class UNetwork;
class UUISystem;
class UNetObjectManager;
class UDataLoadManager;
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
	UFUNCTION(BlueprintCallable)
	void BeginPlay();
	UFUNCTION(BlueprintCallable)
	void EndPlay();
public:
	void ConnectToServer(ServerType Type, SessionFactoryFunc SessionFactory) const;
	void HandlePacket() const;
public:
	void HandleLogin(gen::account::LoginRes* Packet) const;
	void HandleRegister(gen::account::RegisterRes* Packet);
	void HandleCheckNickname(gen::account::CheckNicknameRes* Packet);
	void HandleEnterGame(gen::mmo::EnterGameRes* Packet);
	void HandleEnterMap(gen::mmo::EnterMapRes* Packet);
	void HandleChat(gen::mmo::NotifyChat* Packet);
public:
	static TObjectPtr<UNetwork> Net(const UWorld* World = GEngine->GameViewport->GetWorld());
	static TObjectPtr<UUISystem> UI(const UWorld* World = GEngine->GameViewport->GetWorld());
	static TObjectPtr<UNetObjectManager> Object(const UWorld* World = GEngine->GameViewport->GetWorld());
	static TObjectPtr<UDataLoadManager> DataLoad(const UWorld* World = GEngine->GameViewport->GetWorld());

	static UManager* Get(const UWorld* World = GEngine->GameViewport->GetWorld());
	void Initialize();
private:
	UPROPERTY(EditAnywhere) TSubclassOf<UNetwork> NetworkClass;
	UPROPERTY(EditAnywhere) TSubclassOf<UUISystem> UISystemClass;
	UPROPERTY(EditAnywhere) TSubclassOf<UNetObjectManager> NetObjectManagerClass;
	UPROPERTY(EditAnywhere) TSubclassOf<UDataLoadManager> DataLoadManagerClass;
	UPROPERTY() TObjectPtr<UNetwork> NetworkObject;
	UPROPERTY() TObjectPtr<UUISystem> UISystemObject;
	UPROPERTY() TObjectPtr<UNetObjectManager> NetObjectManagerObject;
	UPROPERTY() TObjectPtr<UDataLoadManager> DataLoadManagerObject;
};
