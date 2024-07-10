// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/JoinUI.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Components/TextBlock.h"
#include "generated/account/ClientPacketHandler.gen.hpp"
#include "Managers/Manager.h"
#include "Managers/Network.h"
#include "Managers/UISystem.h"

void UJoinUI::NativeConstruct() {
	Super::NativeConstruct();
	
	BIDCheck->OnClicked.AddDynamic(this, &UJoinUI::OnClickIDCheck);
	BRegist->OnClicked.AddDynamic(this, &UJoinUI::OnClickRegist);
}

void UJoinUI::NativeTick(const FGeometry& MyGeometry, float InDeltaTime) {
	Super::NativeTick(MyGeometry, InDeltaTime);
	if (PW->GetText().EqualTo(FText::FromString(TEXT("")))) {
		isPWCheck = false;
		TPWCheckResult->SetText(FText::FromString(TEXT("")));
		TPWCheckResult->SetColorAndOpacity(FSlateColor(FLinearColor(1, 0, 0, 1)));
	}
	else if (FText::TrimPrecedingAndTrailing(PW->GetText()).EqualTo(FText::FromString(TEXT("")))) {
		isPWCheck = false;
		TPWCheckResult->SetText(FText::FromString(TEXT("사용할 수 없는 비밀번호입니다.")));
		TPWCheckResult->SetColorAndOpacity(FSlateColor(FLinearColor(1, 0, 0, 1)));
	}
	else if (FText::TrimPrecedingAndTrailing(PW->GetText()).EqualTo(FText::TrimPrecedingAndTrailing(PWCheck->GetText()))) {
		isPWCheck = true;
		TPWCheckResult->SetText(FText::FromString(TEXT("비밀번호가 일치합니다.")));
		TPWCheckResult->SetColorAndOpacity(FSlateColor(FLinearColor(0, 1, 0, 1)));
	}
	else {
		isPWCheck = false;
		TPWCheckResult->SetText(FText::FromString(TEXT("비밀번호가 일치하지 않습니다.")));
		TPWCheckResult->SetColorAndOpacity(FSlateColor(FLinearColor(1, 0, 0, 1)));
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
		isIDCheck = false;
		TIDCheckResult->SetText(FText::FromString(TEXT("이미 사용 중인 아이디입니다.")));
		TIDCheckResult->SetColorAndOpacity(FSlateColor(FLinearColor(1, 0, 0, 1)));	
	}
	else if (FText::TrimPrecedingAndTrailing(ID->GetText()).EqualTo(FText::FromString(TEXT("")))) {
		isIDCheck = false;
		TIDCheckResult->SetText(FText::FromString(TEXT("사용할 수 없는 아이디입니다.")));
		TIDCheckResult->SetColorAndOpacity(FSlateColor(FLinearColor(1, 0, 0, 1)));
	}
	else {
		isIDCheck = true;
		TIDCheckResult->SetText(FText::FromString(TEXT("사용 가능한 아이디입니다.")));
		TIDCheckResult->SetColorAndOpacity(FSlateColor(FLinearColor(0, 1, 0, 1)));
	}
}

void UJoinUI::SuccessRegist() {
	UManager::UI()->HideWidget(WidgetType::Join);

	ID->SetText(FText::FromString(TEXT("")));
	PW->SetText(FText::FromString(TEXT("")));
	PWCheck->SetText(FText::FromString(TEXT("")));
}