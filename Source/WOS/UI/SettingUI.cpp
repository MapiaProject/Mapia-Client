// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SettingUI.h"
#include "Managers/Manager.h"
#include "Managers/UISystem.h"
#include "Components/Button.h"

void USettingUI::NativeConstruct() {
	Super::NativeConstruct();

	BLower->OnClicked.AddDynamic(this, &USettingUI::OnClickLower);
	BUpper->OnClicked.AddDynamic(this, &USettingUI::OnClickUpper);
}

void USettingUI::HideSetting() {
	UManager::UI()->HideWidget(WidgetType::Setting);
}

void USettingUI::OnClickLower() {

}

void USettingUI::OnClickUpper() {

}