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
	
	static ConstructorHelpers::FClassFinder<UUserWidget> FoundLobbyUIClass(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprints/UI/WBP_LoginUI.WBP_LoginUI_C'"));
	if (FoundLobbyUIClass.Succeeded())
	{
		LobbyUIClass = FoundLobbyUIClass.Class;
		CurrentWidget = CreateWidget(GetWorld(), LobbyUIClass);
		if (CurrentWidget) CurrentWidget->AddToViewport();
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> FoundLoginPopup(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprints/UI/WBP_LoginPopup.WBP_LoginPopup_C'"));
	if (FoundLoginPopup.Succeeded())
	{
		LoginPopup = FoundLoginPopup.Class;
	}
}

AWOSGameModeBase::~AWOSGameModeBase()
{
}

void AWOSGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Emerald, TEXT("BeginPlay"));
	
	UManager::Get(GetWorld())->Initialize();
	UManager::Get(GetWorld())->ConnectToServer(ServerType::Account, [](net::Socket* sock)
	{
		return MakeShared<FAccountSession>(sock);
	});
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
