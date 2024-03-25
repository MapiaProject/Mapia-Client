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
	Socket.create(net::Protocol::Tcp);
	const bool bIsConnected = Socket.connect(EndPoint);
	if(bIsConnected)
	{
		const auto Session = SessionFactory(&Socket);
		Session->OnConnected();
		
		AddSession(Type, Session);
	}
	return bIsConnected;
}

void UNetwork::Disconnect()
{
	for (auto& Tuple : Sessions)
	{
		Tuple.Value->GetHandle()->disconnect();
		Tuple.Value = nullptr;
	}
	Sessions.Reset();
}

void UNetwork::Send(ServerType Type, Packet* Packet) const
{
	if (Sessions.Contains(Type))
		Sessions[Type]->Send(Packet);
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
