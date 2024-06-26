// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InventoryUI.h"
#include "Managers/Manager.h"
#include "Managers/UISystem.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"

void UInventoryUI::NativeConstruct() {
	Super::NativeConstruct();

	BDamage->OnClicked.AddDynamic(this, &UInventoryUI::OnClickDamage);
	BSpeed->OnClicked.AddDynamic(this, &UInventoryUI::OnClickSpeed);
	BHealth->OnClicked.AddDynamic(this, &UInventoryUI::OnClickHealth);
	BExit->OnClicked.AddDynamic(this, &UInventoryUI::OnClickExit);
}

void UInventoryUI::HideInventory() {
	UManager::UI()->HideWidget(WidgetType::Inventory);
}

void UInventoryUI::OnClickDamage() {

}

void UInventoryUI::OnClickSpeed() {

}

void UInventoryUI::OnClickHealth() {

}

void UInventoryUI::OnClickExit() {
	UManager::UI()->HideWidget(WidgetType::Inventory);
}