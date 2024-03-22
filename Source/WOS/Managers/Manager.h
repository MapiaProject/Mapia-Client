// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Define.h"
#include "generated/account/Protocol.gen.hpp"
#include "Session/Session.h"
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

class UNetwork;
class UWidget;

/**
 * 
 */
UCLASS()
class WOS_API UManager : public UGameInstance
{
	GENERATED_BODY()
	using SessionFactoryFunc = TFunction<TSharedPtr<FSession>(net::Socket*)>;
public:
	UManager();
	virtual ~UManager() override;
public:
	UFUNCTION(BlueprintCallable)
	void EnterGame();
	
	void ConnectToServer(ServerType server, SessionFactoryFunc SessionFactory) const;
	void HandlePacket() const;
	void DisconnectFromServer() const;
public:
	void HandleLogin(gen::account::LoginRes* Packet);
	void HandleRegister(gen::account::RegisterRes* Packet);
public:
	static TObjectPtr<UNetwork> Net(const UWorld* World = GEngine->GameViewport->GetWorld());

	static UManager* Get(const UWorld* World = GEngine->GameViewport->GetWorld());
	void Initialize();
private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UNetwork> NetworkClass;
	UPROPERTY()
	TObjectPtr<UNetwork> NetworkObject;
};	
