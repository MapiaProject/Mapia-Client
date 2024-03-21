// Fill out your copyright notice in the Description page of Project Settings.


#include "LoginUI.h"

#include "Components/Button.h"

void ULoginUI::NativeConstruct()
{
	Super::NativeConstruct();
	LoginButton->OnClicked.AddDynamic(this, &ULoginUI::OnClickLogin);
	RegisterButton->OnClicked.AddDynamic(this, &ULoginUI::OnClickRegister);
}

void ULoginUI::NativeDestruct()
{
	Super::NativeDestruct();
}

void ULoginUI::OnClickLogin()
{
}

void ULoginUI::OnClickRegister()
{
}
