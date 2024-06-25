// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/UISystem.h"

#include "UI/InGameUI.h"
#include "UI/InventoryUI.h"
#include "UI/LoginUI.h"
#include "UI/LoginFailUI.h"
#include "UI/JoinUI.h"
#include "UI/MenuUI.h"
#include "UI/SettingUI.h"
#include "UI/TitleUI.h"
#include "generated/account/Protocol.gen.hpp"

#define BindWidget(WidgetObject, Type)\
	if (!Type##WidgetObject)\
	{\
		Type##WidgetObject = CreateWidget<U##Type##UI>(GetWorld(), Type##Widget);\
	}\
	WidgetObject = Type##WidgetObject;\

void UUISystem::ShowWidget(WidgetType WidgetType)
{
	UUserWidget* WidgetObject = nullptr;
	
	switch (WidgetType)
	{
	case WidgetType::Inventory:
		BindWidget(WidgetObject, Inventory)
		break;
	case WidgetType::Join:
		BindWidget(WidgetObject, Join)
		break;
	case WidgetType::Login:
		BindWidget(WidgetObject, Login)
		break;
	case WidgetType::LoginFail:
		BindWidget(WidgetObject, LoginFail)
		break;
	case WidgetType::Menu:
		BindWidget(WidgetObject, Menu)
		break;
	case WidgetType::Setting:
		BindWidget(WidgetObject, Setting)
		break;
	case WidgetType::Title:
		BindWidget(WidgetObject, Title)
		break;
	case WidgetType::InGame:
		BindWidget(WidgetObject, InGame)
		break;
	}
	
	if (WidgetObject != nullptr) WidgetObject->AddToViewport();
}

void UUISystem::HideWidget(WidgetType WidgetType)
{
	UUserWidget* WidgetObject = nullptr;
	
	if (WidgetType == WidgetType::Title) WidgetObject = TitleWidgetObject;
	else if (WidgetType == WidgetType::Login) WidgetObject = LoginWidgetObject;
	else if (WidgetType == WidgetType::LoginFail) WidgetObject = LoginFailWidgetObject;
	else if (WidgetType == WidgetType::Join) WidgetObject = JoinWidgetObject;
	else if (WidgetType == WidgetType::InGame) WidgetObject = InGameWidgetObject;
	else if (WidgetType == WidgetType::Inventory) WidgetObject = InventoryWidgetObject;
	else if (WidgetType == WidgetType::Menu) WidgetObject = MenuWidgetObject;
	else if (WidgetType == WidgetType::Setting) WidgetObject = SettingWidgetObject;

	if (WidgetObject != nullptr) WidgetObject->RemoveFromParent();
}

void UUISystem::ExecSuccessLogin() {
	Cast<ULoginUI>(LoginWidgetObject)->SetBlank();
	Cast<ULoginUI>(LoginWidgetObject)->SuccessLogin();
}

void UUISystem::ExecFailedLogin(int cause) {
	ShowWidget(WidgetType::LoginFail);
	Cast<ULoginUI>(LoginWidgetObject)->SetBlank();
	Cast<ULoginFailUI>(LoginFailWidgetObject)->SetCause(cause);
}

void UUISystem::ExecIDCheckResult(bool result) {
	Cast<UJoinUI>(JoinWidgetObject)->IDCheckResult(result);
}

void UUISystem::ExecSuccessRegist() {
	Cast<UJoinUI>(JoinWidgetObject)->SuccessRegist();
}

void UUISystem::ExecAddChatHistory(FString Message, FLinearColor TextColor) {
	Cast<UInGameUI>(InGameWidgetObject)->AddChatHistory(Message, TextColor);
}

void UUISystem::ExecLocalPlayerSetHP(float MaxHP, float CurHP)
{
	Cast<UInGameUI>(InGameWidgetObject)->SetHP(MaxHP, CurHP);
}
