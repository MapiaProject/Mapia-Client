// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "generated/mmo/ClientPacketHandler.gen.hpp"
#include "Managers/Manager.h"
#include "Managers/Network.h"
#include "net/Socket.hpp"
#include "Session/Session.h"

/**
 * 
 */
class WOS_API FIoThread : FRunnable
{
	using SessionFactoryFunc = TFunction<TSharedPtr<FSession>(net::Socket*)>;
public:
	FIoThread(ServerType Type, net::Socket* Sock, SessionFactoryFunc SessionFactory) : Session(SessionFactory(Sock))
	{
		UManager::Net()->AddSession(Type, Session);
		Session->OnConnected();
		Thread = FRunnableThread::Create(this, TEXT("Net I/O Thread"));
	}
	virtual ~FIoThread() override;
public:
	virtual bool Init() override;
	virtual uint32 Run() override;
	virtual void Stop() override;
	virtual void Exit() override;
public:
	void Send(class Packet* packet);
private:
	FRunnableThread* Thread;
	TSharedPtr<FSession> Session;
	FCriticalSection CriticalSection;
};
