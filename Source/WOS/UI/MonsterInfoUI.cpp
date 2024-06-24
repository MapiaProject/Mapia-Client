// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MonsterInfoUI.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"

void UMonsterInfoUI::NativeConstruct() {
	Super::NativeConstruct();

	TName->SetText(FText::FromString(TEXT("gkgkgkgkgkgkgk")));
}

void UMonsterInfoUI::SetHP(float curHP, float maxHP) {
	HPBar->SetPercent(curHP / maxHP);
}