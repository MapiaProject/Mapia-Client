// Fill out your copyright notice in the Description page of Project Settings.


#include "WOSGameModeBase.h"
#include "Managers/Manager.h"
#include "Blueprint/UserWidget.h"
#include "generated/mmo/ClientPacketHandler.gen.hpp"
#include "Session/AccountSession.h"

AWOSGameModeBase::AWOSGameModeBase() : Super(), CurrentWidget(nullptr)
{
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bCanEverTick = true;
	
	static ConstructorHelpers::FClassFinder<UUserWidget> FindLobbyUIClass(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprints/UI/WBP_LoginUI.WBP_LoginUI_C'"));
	if (FindLobbyUIClass.Succeeded())
	{
		LobbyUIClass = FindLobbyUIClass.Class;
		CurrentWidget = CreateWidget(GetWorld(), LobbyUIClass);
		if (CurrentWidget)
		{
			CurrentWidget->AddToViewport();
		}
	}
}

AWOSGameModeBase::~AWOSGameModeBase()
{
}

void AWOSGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	UManager::Instance(GetWorld())->Initialize();
	UManager::Instance(GetWorld())->ConnectToServer(ServerType::Account, [](net::Socket* sock)
	{
		return MakeShared<FAccountSession>(sock);
	});
}

void AWOSGameModeBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	UManager::Instance(GetWorld())->HandlePacket();
}

void AWOSGameModeBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}
