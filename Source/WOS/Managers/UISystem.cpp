// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/UISystem.h"

#include "WOSGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "UI/LoginPopup.h"
#include "UI/InventoryUI.h"
#include "UI/Login.h"
#include "UI/JoinUI.h"

void UUISystem::ShowWidget(WidgetType widgetType)
{
	UUserWidget* WidgetObject = nullptr;

	if (widgetType == WidgetType::Title) WidgetObject = TitleWidgetObject == nullptr ? CreateWidget<UInventoryUI>(GetWorld(), TitleWidget), TitleWidgetObject = WidgetObject : TitleWidgetObject;
	else if (widgetType == WidgetType::Login) WidgetObject = LoginWidgetObject == nullptr ? CreateWidget<UInventoryUI>(GetWorld(), LoginWidget), LoginWidgetObject = WidgetObject : LoginWidgetObject;
	else if (widgetType == WidgetType::Join) WidgetObject = JoinWidgetObject == nullptr ? CreateWidget<UInventoryUI>(GetWorld(), JoinWidget), JoinWidgetObject = WidgetObject : JoinWidgetObject;
	else if (widgetType == WidgetType::InGame) WidgetObject = InGameWidgetObject == nullptr ? CreateWidget<UInventoryUI>(GetWorld(), InGameWidget), InGameWidgetObject = WidgetObject : InGameWidgetObject;
	else if (widgetType == WidgetType::Inventory) WidgetObject = InventoryWidgetObject == nullptr ? CreateWidget<UInventoryUI>(GetWorld(), InventoryWidget), InventoryWidgetObject = WidgetObject : InventoryWidgetObject;
	else if (widgetType == WidgetType::Menu) WidgetObject = MenuWidgetObject == nullptr ? CreateWidget<UInventoryUI>(GetWorld(), MenuWidget), MenuWidgetObject = WidgetObject : MenuWidgetObject;
	else if (widgetType == WidgetType::Setting) WidgetObject = SettingWidgetObject == nullptr ? CreateWidget<UInventoryUI>(GetWorld(), SettingWidget), SettingWidgetObject = WidgetObject : SettingWidgetObject;
	
	if (WidgetObject != nullptr) WidgetObject->AddToViewport();
}

void UUISystem::HideWidget(WidgetType widgetType)
{
	UUserWidget* WidgetObject = nullptr;
	
	if (widgetType == WidgetType::Title) WidgetObject = TitleWidgetObject;
	else if (widgetType == WidgetType::Login) WidgetObject = LoginWidgetObject;
	else if (widgetType == WidgetType::Join) WidgetObject = JoinWidgetObject;
	else if (widgetType == WidgetType::InGame) WidgetObject = InGameWidgetObject;
	else if (widgetType == WidgetType::Inventory) WidgetObject = InventoryWidgetObject;
	else if (widgetType == WidgetType::Menu) WidgetObject = MenuWidgetObject;
	else if (widgetType == WidgetType::Setting) WidgetObject = SettingWidgetObject;

	if (WidgetObject != nullptr) WidgetObject->RemoveFromViewport();
}

void UUISystem::ExecSuccessLogin() {
	Cast<ULogin>(LoginWidgetObject)->SuccessLogin();
}

void UUISystem::ExecIDCheckResult(bool result) {
	Cast<UJoinUI>(JoinWidgetObject)->IDCheckResult(result);
}

void UUISystem::ExecSuccessRegist() {
	Cast<UJoinUI>(JoinWidgetObject)->SuccessRegist();
}