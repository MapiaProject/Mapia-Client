// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PlayerInfoUI.h"
#include "Components/TextBlock.h"

void UPlayerInfoUI::SetName(FString Name) {
	TName->SetText(FText::FromString(Name));
}