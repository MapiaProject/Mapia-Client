// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/JoinUI.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "generated/account/ClientPacketHandler.gen.hpp"
#include "Managers/Manager.h"
#include "Managers/Network.h"
#include "Managers/UISystem.h"

void UJoinUI::NativeConstruct() {
	Super::NativeConstruct();
	
	BIDCheck->OnClicked.AddDynamic(this, &UJoinUI::OnClickIDCheck);
	BRegist->OnClicked.AddDynamic(this, &UJoinUI::OnClickRegist);
	isIDCheck = true;
}

void UJoinUI::NativeTick(const FGeometry& MyGeometry, float InDeltaTime) {
	Super::NativeTick(MyGeometry, InDeltaTime);
	if (PW->GetText().ToString() == PWCheck->GetText().ToString() && PW->GetText().ToString() != "") {
		isPWCheck = true;
	}
	else {
		isPWCheck = false;
	}
}

void UJoinUI::OnClickIDCheck() {
	gen::account::CheckNicknameReq req;
	req.nickname = ID->GetText().ToString();
	UManager::Net()->Send(ServerType::Account, &req);
}

void UJoinUI::OnClickRegist() {
	if (isIDCheck && isPWCheck) {
		gen::account::RegisterReq req;
		req.nickname = ID->GetText().ToString();
		req.password = FMD5::HashAnsiString(*PW->GetText().ToString());
		UManager::Net()->Send(ServerType::Account, &req);
	}
}

void UJoinUI::IDCheckResult(bool result) {
	if (result) {
		isIDCheck = true;
		TIDCheckResult->SetText(FText::FromString(TEXT("사용 가능한 아이디 입니다.")));
		TIDCheckResult->SetForegroundColor(FLinearColor(0, 1, 0, 1));
	}
	else {
		isPWCheck = true;
		TIDCheckResult->SetText(FText::FromString(TEXT("중복된 아이디 입니다.")));
		TIDCheckResult->SetForegroundColor(FLinearColor(1, 0, 0, 1));
	}
}

void UJoinUI::SuccessRegist() {
	UManager::UI()->HideWidget(WidgetType::Join);

	ID->SetText(FText::FromString(TEXT("")));
	PW->SetText(FText::FromString(TEXT("")));
	PWCheck->SetText(FText::FromString(TEXT("")));
}