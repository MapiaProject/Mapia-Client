// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager.h"

#include "WOSGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Network/Session/Session.h"
#include "Managers/Network.h"
#include "Session/MMOSession.h"
#include "UI/LoginPopup.h"

UManager::UManager() : NetworkObject(nullptr)
{
	NetworkClass = UNetwork::StaticClass();
}

UManager::~UManager()
{
}

void UManager::EnterGame()
{
	if (NetworkObject)
	{
		// auto packet = gen::EnterGameReq {};
		// NetworkObject->Send(&packet);
	}
}

void UManager::ConnectToServer(ServerType server, SessionFactoryFunc SessionFactory) const
{
	if (!NetworkObject->Connect(net::Endpoint(net::IpAddress::Loopback, static_cast<uint16>(server)), SessionFactory))
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
	if(!NetworkObject)
		return;
	if (!NetworkObject->IsConnected())
	{

	}
}

void UManager::HandleLogin(gen::account::LoginRes* Packet)
{
	if (Packet->success)
	{
		ConnectToServer(ServerType::MMO, [](net::Socket* sock)
		{
			return MakeShared<FMMOSession>(sock);
		});
	}
	else
	{
		auto World = GEngine->GameViewport->GetWorld();
		auto WOSGameMode = Cast<AWOSGameModeBase>(UGameplayStatics::GetGameMode(World));
		
		auto Popup = Cast<ULoginPopup>(CreateWidget(World, WOSGameMode->LoginPopup));
		if (Popup)
		{
			Popup->AddToViewport();
			Popup->SetTitle(FText::FromString(TEXT("알림")));

			switch(Packet->cause)
			{
			case gen::account::ELoginFail::EXIST:
				Popup->SetContent(FText::FromString(TEXT("이미 접속중인 계정입니다.")));
				break;
			case gen::account::ELoginFail::INVALID:
				Popup->SetContent(FText::FromString(TEXT("비밀번호 또는 닉네임이 일치하지 않습니다.")));
				break;
			}
		}	
	}
}

void UManager::HandleRegister(gen::account::RegisterRes* Packet)
{
	if (Packet->success)
	{
		ConnectToServer(ServerType::MMO, [](net::Socket* sock)
		{
			return MakeShared<FMMOSession>(sock);
		});
	}
	else
	{
		auto World = GEngine->GameViewport->GetWorld();
		auto WOSGameMode = Cast<AWOSGameModeBase>(UGameplayStatics::GetGameMode(World));
		auto Popup = Cast<ULoginPopup>(CreateWidget(World, WOSGameMode->LoginPopup));
		if (Popup)
		{
			Popup->AddToViewport();
			Popup->SetTitle(FText::FromString(TEXT("알림")));
			Popup->SetContent(FText::FromString(TEXT("이미 존재하는 닉네임입니다.")));
		}	
	}	
}

TObjectPtr<UNetwork> UManager::Net(const UWorld* World)
{
	return Get(World)->NetworkObject;
}

UManager* UManager::Get(const UWorld* World)
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

