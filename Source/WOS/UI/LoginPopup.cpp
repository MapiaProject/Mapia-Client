// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/LoginPopup.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"

void ULoginPopup::NativeConstruct()
{
	Super::NativeConstruct();
	CancelButton->OnClicked.AddDynamic(this, &ULoginPopup::OnClick);
}

void ULoginPopup::NativeDestruct()
{
	Super::NativeDestruct();
}

void ULoginPopup::SetTitle(FText TitleName)
{
	Title->SetText(TitleName);
}

void ULoginPopup::SetContent(FText ContentText)
{
	this->Content->SetText(ContentText);
}

void ULoginPopup::OnClick()
{
	RemoveFromParent();
}
