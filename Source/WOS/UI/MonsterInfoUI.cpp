// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MonsterInfoUI.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"

void UMonsterInfoUI::SetHP(float MaxHP, float CurHP) {
	HPBar->SetPercent(MaxHP / CurHP);
	THP->SetText(FText::FromString(FString::Printf(TEXT("%.0f/%.0f"), CurHP, MaxHP)));
}

void UMonsterInfoUI::SetName(FString Name) {
	TName->SetText(FText::FromString(Name));
}