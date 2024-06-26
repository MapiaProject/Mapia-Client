// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager.h"

#include "MHGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Network/Session.h"
#include "UI/LobbyUI.h"

UManager::UManager() : NetworkObject(nullptr)
{
	NetworkClass = UNetwork::StaticClass();
}

UManager::~UManager()
{
}

void UManager::ConnectToServer() const
{
	if (!NetworkObject->Connect(net::Endpoint(net::IpAddress::Loopback, 9999)))
	{
		UE_LOG(LogNet, Warning, TEXT("Can't connect with server."));
		UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(), EQuitPreference::Type::Quit, false);
	}
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
	if (!NetworkObject)
		return;
	if (!NetworkObject->IsConnected())
	{

	}
}

void UManager::EnterRoom(uint32 Id)
{
	CurrentRoomId = Id;
	
	gen::RoomEventReq enterEvent;
	enterEvent.event = gen::ENTER;
	enterEvent.room.id = Id;
	NetworkObject->Send(&enterEvent);
}

void UManager::LeaveRoom()
{
	if (CurrentRoomId.has_value())
	{
		gen::RoomEventReq EventReq;
		EventReq.event = gen::LEAVE;
		EventReq.room.id = CurrentRoomId.value();
		NetworkObject->Send(&EventReq);
	}
}

void UManager::RefreshRoom(gen::NotifyRoomList RoomList)
{
	for (const auto& room : RoomList.roomList)
	{
		auto GameMode = Cast<AMHGameModeBase>(UGameplayStatics::GetGameMode(GEngine->GameViewport->GetWorld()));
		if (auto LobbyUI = Cast<ULobbyUI>(GameMode->CurrentWidget))
		{
			LobbyUI->AddRoom(room.id, room.name);
		}
		else return;
	}
}

void UManager::HandleRoomEventResult(gen::RoomEventRes EventRes)
{
	switch (EventRes.event)
	{
	case gen::ENTER:
		if (EventRes.success)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Emerald, TEXT("ENTER!"));
		}
		else CurrentRoomId = std::nullopt;
		break;
	case gen::LEAVE:
		break;
	case gen::CREATE:
		break;
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
	auto manager = CastChecked<UManager>(World->GetGameInstance());
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

