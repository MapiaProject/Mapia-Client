// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/LoginFailUI.h"
#include "Components/EditableTextBox.h"
#include "Managers/Manager.h"
#include "Managers/UISystem.h"
#include "generated/account/Protocol.gen.hpp"
#include <iostream>

void ULoginFailUI::NativeTick(const FGeometry& MyGeometry, float InDeltaTime) {
	Super::NativeTick(MyGeometry, InDeltaTime);
	
	isOnFailUI = this->IsInViewport();

	if (isOnFailUI) {
		HoldingTime += InDeltaTime;
		if (HoldingTime >= 1.5f) {
			HoldingTime = 0;
			UManager::UI()->HideWidget(WidgetType::LoginFail);
		}
	}
}

void ULoginFailUI::SetCause(int cause) {
	switch (gen::account::ELoginFail(cause)) {
	case gen::account::ELoginFail::EXIST:
		TCause->SetText(FText::FromString(TEXT("이미 접속 중인 계정입니다.")));
		break;
	case gen::account::ELoginFail::INVALID:
		TCause->SetText(FText::FromString(TEXT("잘못된 계정 정보입니다.")));
		break;
	}
}