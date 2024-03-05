// Fill out your copyright notice in the Description page of Project Settings.


#include "MHGameModeBase.h"
#include "Managers/Manager.h"
#include "Blueprint/UserWidget.h"

AMHGameModeBase::AMHGameModeBase() : Super(), CurrentWidget(nullptr)
{
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bCanEverTick = true;
	
	static ConstructorHelpers::FClassFinder<UUserWidget> FindTitleUIClass(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprints/UI/WBP_TitleUI.WBP_TitleUI_C'"));
	if (FindTitleUIClass.Succeeded())
	{
		TitleUIClass = FindTitleUIClass.Class;
		CurrentWidget = CreateWidget(GetWorld(), TitleUIClass);
		if (CurrentWidget)
		{
			CurrentWidget->AddToViewport();
		}
	}
	static ConstructorHelpers::FClassFinder<UUserWidget> FindLobbyUIClass(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprints/UI/WBP_LobbyUI.WBP_LobbyUI_C'"));
	if (FindLobbyUIClass.Succeeded())
	{
		LobbyUIClass = FindLobbyUIClass.Class;
	}
}

AMHGameModeBase::~AMHGameModeBase()
{
}

void AMHGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	UManager::Instance(GetWorld())->Initialize();
	UManager::Instance(GetWorld())->ConnectToServer();
}

void AMHGameModeBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	UManager::Instance(GetWorld())->HandlePacket();
}

void AMHGameModeBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	UManager::Instance(GetWorld())->LeaveRoom();
}
