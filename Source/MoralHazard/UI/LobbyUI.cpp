// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/LobbyUI.h"

#include "RoomButton.h"
#include "Blueprint/WidgetTree.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Kismet/GameplayStatics.h"

void ULobbyUI::NativeConstruct()
{
	Super::NativeConstruct();

	if (auto Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0))
	{
		Controller->bShowMouseCursor = true;
	}
}

void ULobbyUI::AddRoom(uint32 Id, FStringView Name) const
{
	auto Btn = WidgetTree->ConstructWidget<URoomButton>(RoomButton, Name.GetData());
	Btn->RoomId = Id;
	Btn->RoomName->SetText(FText::FromString(Name.GetData()));
	RoomListVerticalBox->AddChild(Btn);
}
