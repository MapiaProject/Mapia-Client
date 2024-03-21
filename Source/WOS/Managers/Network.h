// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "ManagerBase.h"

#include "net/Socket.hpp"
#include "Network.generated.h"

class FSession;
class ANetworkCharacter;
/**
 * 
 */
UCLASS()
class WOS_API UNetwork : public UManagerBase
{
	GENERATED_BODY()
	friend class FIoThread;
	
	using SessionFactoryFunc = TFunction<TSharedPtr<FSession>(net::Socket*)>;
public:
	UNetwork();
	virtual ~UNetwork() override;
public:
	bool Connect(const net::Endpoint& EndPoint, SessionFactoryFunc SessionFactory);
	void Disconnect();
	bool IsConnected() const;
	void Send(class Packet* Packet) const;
public:
	void SetSession(const TSharedPtr<FSession>& NewSession);
	TSharedPtr<FSession> GetSession();
private:
	bool bIsConnected;
	FIoThread* IoThread;
	net::Socket Socket;
	TSharedPtr<FSession> Session;
};
