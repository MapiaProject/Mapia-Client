// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <optional>

#include "CoreMinimal.h"
#include "Define.h"
#include "ManagerBase.h"
#include "net/netcpp.hpp"
#include "Network.generated.h"

class FSession;
/**
 * 
 */

UCLASS()
class WOS_API UNetwork : public UManagerBase
{
	GENERATED_BODY()
	friend class FIoThread;
	
	using SessionFactoryFunc = TFunction<TSharedPtr<FSession>(TSharedPtr<net::Socket>)>;
public:
	UNetwork();
	virtual ~UNetwork() override;
public:
	bool Connect(ServerType Type, const net::Endpoint& EndPoint, SessionFactoryFunc SessionFactory);
	void Disconnect();
	void Send(ServerType Type, class Packet* Packet) const;
public:
	void AddSession(ServerType Type, TSharedPtr<FSession> NewSession);
	TArray<TSharedPtr<FSession>> GetSessions();
public:
	void SetUUID(FString Uuid);
	std::optional<FString> GetUUID() const;
private:
	TMap<ServerType, TSharedPtr<FSession>> Sessions;
	std::optional<FString> UUID;
};
