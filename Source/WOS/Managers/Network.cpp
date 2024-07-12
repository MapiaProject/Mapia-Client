// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/Network.h"
#include "Session/Session.h"

UNetwork::UNetwork()
{
}

UNetwork::~UNetwork()
{
}

bool UNetwork::Connect(ServerType Type, const net::Endpoint& EndPoint, SessionFactoryFunc SessionFactory)
{
	auto Socket = MakeShared<net::Socket>(net::Protocol::Tcp);
	const bool bIsConnected = Socket->connect(EndPoint);
	if(bIsConnected)
	{
		const auto Session = SessionFactory(Socket);
		Session->OnConnected();
		
		AddSession(Type, Session);
	}
	return bIsConnected;
}

void UNetwork::Disconnect()
{
	for (auto& Tuple : Sessions)
	{
		Tuple.Value->Disconnect();
		Tuple.Value = nullptr;
	}
	Sessions.Reset();
}

void UNetwork::Send(ServerType Type, Packet* Packet) const
{
	if (Sessions.Contains(Type))
		Sessions[Type]->Send(Packet);
}

void UNetwork::AddSession(ServerType Type, FSession* NewSession)
{
	this->Sessions.Add(Type, NewSession);
}

void UNetwork::RemoveSession(ServerType Type)
{
	Sessions.Remove(Type);
}

TArray<FSession*> UNetwork::GetSessions()
{
	TArray<FSession*> SessionArray;
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
