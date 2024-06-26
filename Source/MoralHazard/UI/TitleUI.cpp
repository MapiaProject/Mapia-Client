// Fill out your copyright notice in the Description page of Project Settings.


#include "TitleUI.h"

#include "Components/Button.h"
#include "MHGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Managers/Manager.h"
#include "Managers/Network.h"
#include "Network/generated/Protocol.gen.hpp"

void UTitleUI::NativeConstruct()
{
	Super::NativeConstruct();
	if (auto Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0))
	{
		Controller->bShowMouseCursor = true;
	}
	Background->OnClicked.AddDynamic(this, &UTitleUI::OnClick);
}

void UTitleUI::OnClick()
{
	gen::EnterGameReq EnterGame;
	UManager::Net()->Send(&EnterGame);
	
	RemoveFromParent();
	auto* gameMode = CastChecked<AMHGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	gameMode->CurrentWidget = CreateWidget(GetWorld(), gameMode->LobbyUIClass);
	if (gameMode->CurrentWidget)
	{
		gameMode->CurrentWidget->AddToViewport();
	}
}
