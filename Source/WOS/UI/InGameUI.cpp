// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGameUI.h"
#include "Components/ProgressBar.h"
#include "Components/EditableTextBox.h"
#include "Managers/Manager.h"
#include "Managers/UISystem.h"

void UInGameUI::ShowInventory() {
	UManager::UI()->ShowWidget(WidgetType::Inventory);
}

void UInGameUI::ShowMenu() {
	UManager::UI()->ShowWidget(WidgetType::Menu);
}

void UInGameUI::ShowHP(float MaxHP, float CurHP) {
	HPBar->Percent = CurHP / MaxHP;
	THP->SetText(FText::FromString(FString::Printf(TEXT("%.2f / %.2f"), CurHP, MaxHP)));
}