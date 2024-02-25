// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager.h"

#include "Kismet/GameplayStatics.h"
#include "Network/Session.h"
#include "Managers/Network.h"
#include "Components/Widget.h"

UManager::UManager() : NetworkObject(nullptr)
{
	NetworkClass = UNetwork::StaticClass();
}

UManager::~UManager()
{
}

void UManager::BeginPlay()
{
	Initialize();
	ConnectToServer();
}

void UManager::Tick()
{
	HandlePacket();
}

void UManager::EndPlay()
{
	DisconnectFromServer();
}

void UManager::EnterGame()
{
	if (NetworkObject)
	{
		auto packet = gen::EnterGameReq {};
		NetworkObject->Send(&packet);
	}
}

void UManager::ConnectToServer() const
{
	if (!NetworkObject->Connect(net::Endpoint(net::IpAddress::Loopback, 9999)))
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("Connect failed."));
}

void UManager::HandlePacket() const
{
	if (!NetworkObject)
		return;
	if (NetworkObject->IsConnected())
		NetworkObject->GetSession()->Flush();
}

void UManager::DisconnectFromServer() const
{
	if(!NetworkObject)
		return;
	if (!NetworkObject->IsConnected())
	{

	}
}

TObjectPtr<UNetwork> UManager::Net(const UWorld* World)
{
	return Instance(World)->NetworkObject;
}

UManager* UManager::Instance(const UWorld* World)
{
	if (World == nullptr)
		return nullptr;
	auto manager = CastChecked<UManager>(UGameplayStatics::GetGameInstance(World));
	if (manager != nullptr)
	{
		manager->Initialize();
		return manager;
	}
#if WITH_EDITOR
	UE_LOG(LogTemp, Error, TEXT("Invalid Game Instance"));
#endif
	
	auto instance = NewObject<UManager>();
	instance->Initialize();
	return instance;
}

void UManager::Initialize()
{
	INIT_MANAGER(Network);
}

