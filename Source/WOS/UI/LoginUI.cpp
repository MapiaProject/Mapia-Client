// Fill out your copyright notice in the Description page of Project Settings.


#include "LoginUI.h"

#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "generated/account/ClientPacketHandler.gen.hpp"
#include "Managers/Manager.h"
#include "Managers/Network.h"

void ULoginUI::NativeConstruct()
{
	Super::NativeConstruct();

	auto Controller = GetWorld()->GetFirstPlayerController();
	if (Controller)
	{
		Controller->bShowMouseCursor = true;
		Controller->bEnableClickEvents = true;
		Controller->bEnableMouseOverEvents = true;
	}
	
	LoginButton->OnClicked.AddDynamic(this, &ULoginUI::OnClickLogin);
	RegisterButton->OnClicked.AddDynamic(this, &ULoginUI::OnClickRegister);
}

void ULoginUI::NativeDestruct()
{
	Super::NativeDestruct();
}

void ULoginUI::OnClickLogin()
{
	gen::account::LoginReq req;
	req.nickname = ID->GetText().ToString();
	req.password = FMD5::HashAnsiString(*Password->GetText().ToString());
	UManager::Net()->Send(ServerType::Account, &req);

	Reset();
}

void ULoginUI::OnClickRegister()
{
	gen::account::RegisterReq req;
	req.nickname = ID->GetText().ToString();
	req.password = FMD5::HashAnsiString(*Password->GetText().ToString());
	UManager::Net()->Send(ServerType::Account, &req);

	Reset();
}

void ULoginUI::Reset()
{
	ID->SetText(FText::FromString(TEXT("")));
	Password->SetText(FText::FromString(TEXT("")));
}
