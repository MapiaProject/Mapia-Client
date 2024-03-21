// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/Network.h"
#include "Network/IoThread.h"

UNetwork::UNetwork() : bIsConnected(false), IoThread(nullptr)
{
}

UNetwork::~UNetwork()
{
}

bool UNetwork::Connect(const net::Endpoint& EndPoint, SessionFactoryFunc SessionFactory)
{
	Socket.create(net::Protocol::Tcp);
	bIsConnected = Socket.connect(EndPoint);
	if (bIsConnected)
	{
		IoThread = new ::FIoThread(&Socket, SessionFactory);
	}
	return bIsConnected;
}

void UNetwork::Disconnect()
{
	if (bIsConnected)
	{
		bIsConnected = false;
		Socket.disconnect();
		Socket.close();

		delete IoThread;
	}
}

bool UNetwork::IsConnected() const
{
	return bIsConnected;
}

void UNetwork::Send(Packet* Packet) const
{
	if (Session)
		Session->Send(Packet);
}

void UNetwork::SetSession(const TSharedPtr<FSession>& NewSession)
{
	this->Session = NewSession;
}
 
TSharedPtr<FSession> UNetwork::GetSession()
{
	return Session;
}