// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager.h"

#include "UISystem.h"
#include "WOSGameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "generated/mmo/ClientPacketHandler.gen.hpp"
#include "Kismet/GameplayStatics.h"
#include "Network/Session/Session.h"
#include "Managers/Network.h"
#include "Session/MMOSession.h"
#include "GameActor/PlayerCharacter.h"
#include "Managers/NetObjectManager.h"
#include "Util/NetUtility.h"

UManager::UManager() : NetworkObject(nullptr)
{
	NetworkClass = UNetwork::StaticClass();
	UISystemClass = UUISystem::StaticClass();
	NetObjectManagerClass = UNetObjectManager::StaticClass();
}

UManager::~UManager()
{
}

void UManager::BeginPlay()
{
	UI(GetWorld())->ShowWidget(WidgetType::Title);
}

void UManager::EndPlay()
{
}

void UManager::ConnectToServer(ServerType Type, SessionFactoryFunc SessionFactory) const
{
	if (!NetworkObject->Connect(Type, net::Endpoint(net::IpAddress::Loopback, static_cast<uint16>(Type)), SessionFactory))
	{
		UE_LOG(LogNet, Warning, TEXT("Can't connect with server."));
		UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(), EQuitPreference::Type::Quit, false);
	}
}

void UManager::HandlePacket() const
{
	if (!NetworkObject)
		return;
	const auto& Sessions = NetworkObject->GetSessions();
	for (const auto& Session : Sessions)
		Session->Flush();
}

void UManager::HandleLogin(gen::account::LoginRes* Packet) const
{
	auto World = GetWorld();
	if (Packet->success)
	{
		NetworkObject->SetUUID(Packet->uuid);
		ConnectToServer(ServerType::MMO, [](TSharedPtr<net::Socket> Socket)
			{
				auto Session = MakeShared<FMMOSession>(Socket);
				return Session;
			});

		UI(World)->ExecSuccessLogin();
	}
}

void UManager::HandleRegister(gen::account::RegisterRes* Packet)
{
	auto World = GetWorld();
	if (Packet->success)
	{
		UI(World)->ExecSuccessRegist();
	}
}

void UManager::HandleCheckNickname(gen::account::CheckNicknameRes* Packet) {
	UI(GetWorld())->ExecIDCheckResult(Packet->exists);
}

void UManager::HandleEnterGame(gen::mmo::EnterGameRes* Packet)
{
	if (NetworkObject->GetUUID().has_value())
	{
		Object(GetWorld())->RequestEnterMap(TEXT("Village"));
	}
}

void UManager::HandleEnterMap(gen::mmo::EnterMapRes* Packet)
{
	Object(GetWorld())->HandleEnterMap(Packet);
}

TObjectPtr<UNetwork> UManager::Net(const UWorld* World)
{
	return Get(World)->NetworkObject;
}

TObjectPtr<UUISystem> UManager::UI(const UWorld* World)
{
	return Get(World)->UISystemObject;
}

TObjectPtr<UNetObjectManager> UManager::Object(const UWorld* World)
{
	return Get(World)->NetObjectManagerObject;
}

UManager* UManager::Get(const UWorld* World)
{
	if (World == nullptr)
		return nullptr;
	const auto Manager = CastChecked<UManager>(UGameplayStatics::GetGameInstance(World));
	if (Manager != nullptr)
	{
		Manager->Initialize();
		return Manager;
	}
#if WITH_EDITOR
	UE_LOG(LogTemp, Error, TEXT("Invalid Game Instance"));
#endif

	const auto Instance = NewObject<UManager>();
	Instance->Initialize();
	return Instance;
}

void UManager::Initialize()
{
	INIT_MANAGER(Network);
	INIT_MANAGER(UISystem);
	INIT_MANAGER(NetObjectManager);
}

