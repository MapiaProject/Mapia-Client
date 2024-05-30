// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MenuUI.h"
#include "Components/Button.h"
#include "Managers/Manager.h"
#include "Managers/Network.h"
#include "Managers/UISystem.h"
#include "generated/account/ClientPacketHandler.gen.hpp"
#include <Kismet/KismetSystemLibrary.h>

void UMenuUI::NativeConstruct() {
	Super::NativeConstruct();

	BSetting->OnClicked.AddDynamic(this, &UMenuUI::OnClickSetting);
	BLogout->OnClicked.AddDynamic(this, &UMenuUI::OnClickLogout);
	BLeave->OnClicked.AddDynamic(this, &UMenuUI::OnClickLeave);
}

void UMenuUI::OnClickSetting() {
	UManager::UI(GetWorld())->ShowWidget(WidgetType::Setting);
}

void UMenuUI::OnClickLogout() {
	gen::account::LogoutReq req;
	UManager::Net()->Send(ServerType::Account, &req);

	UManager::UI(GetWorld())->ShowWidget(WidgetType::Title);
	UManager::UI(GetWorld())->HideWidget(WidgetType::Setting);
}

void UMenuUI::OnClickLeave() {
	UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, true);
}