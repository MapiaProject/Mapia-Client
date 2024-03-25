// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/Network.h"
#include "Network/IoThread.h"

UNetwork::UNetwork() : bIsConnected(false), IoThread(nullptr)
{
}

UNetwork::~UNetwork()
{
}

bool UNetwork::Connect(ServerType Type, const net::Endpoint& EndPoint, SessionFactoryFunc SessionFactory)
{
	Socket.create(net::Protocol::Tcp);
	bIsConnected = Socket.connect(EndPoint);
	if (bIsConnected)
	{
		IoThread = new ::FIoThread(Type, &Socket, SessionFactory);
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

void UNetwork::Send(ServerType Type, Packet* Packet) const
{
	auto Session = Sessions[Type];
	if (Session != nullptr)
		Session->Send(Packet);
}

void UNetwork::AddSession(ServerType Type, const TSharedPtr<FSession>& NewSession)
{
	this->Sessions.Add(Type, NewSession);
}

TArray<TSharedPtr<FSession>> UNetwork::GetSessions()
{
	TArray<TSharedPtr<FSession>> SessionArray;
	for(auto Tuple : Sessions)
	{
		SessionArray.Add(Tuple.Value);
	}
	return SessionArray;
}

void UNetwork::SetUUID(FString Uuid)
{
	this->UUID = Uuid;
}

std::optional<FString> UNetwork::GetUUID() const
{
	return UUID;
}
