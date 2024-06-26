// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/TitleUI.h"
#include "Components/Button.h"
#include "Managers/UISystem.h"
#include "Managers/Manager.h"

void UTitleUI::NativeConstruct() {
	Super::NativeConstruct();
	
	BStart->OnClicked.AddDynamic(this, &UTitleUI::OnClickStart);
}

void UTitleUI::OnClickStart() {

	UManager::UI(GetWorld())->ShowWidget(WidgetType::Login);
	UManager::UI(GetWorld())->HideWidget(WidgetType::Title);
}