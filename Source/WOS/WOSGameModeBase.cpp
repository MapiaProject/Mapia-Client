// Fill out your copyright notice in the Description page of Project Settings.


#include "WOSGameModeBase.h"
#include "Managers/Manager.h"
#include "Blueprint/UserWidget.h"
#include "Managers/Network.h"
#include "Session/AccountSession.h"
#include "UObject/ConstructorHelpers.h"

AWOSGameModeBase::AWOSGameModeBase() : Super(), CurrentWidget(nullptr)
{
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bCanEverTick = true;
}

AWOSGameModeBase::~AWOSGameModeBase()
{
}

void AWOSGameModeBase::BeginPlay()
{	
	Super::BeginPlay();
	
	if (!UManager::Get()->IsConnected) {
		UManager::Get(GetWorld())->Initialize();
		UManager::Get(GetWorld())->ConnectToServer(ServerType::Account, [](TSharedPtr<net::Socket> Socket)
			{
				auto Session = MakeShared<FAccountSession>(Socket);
				return Session;
			});
	}
}

void AWOSGameModeBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	UManager::Get(GetWorld())->HandlePacket();
}

void AWOSGameModeBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}
