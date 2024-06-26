// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/RoomButton.h"

#include "Components/Button.h"
#include "Managers/Manager.h"
#include "Network/generated/Protocol.gen.hpp"

void URoomButton::NativeConstruct()
{
	Super::NativeConstruct();
	RoomButton->OnClicked.AddDynamic(this, &URoomButton::OnClick);
}

void URoomButton::OnClick()
{
	UManager::Instance(GetWorld())->EnterRoom(RoomId);
}
