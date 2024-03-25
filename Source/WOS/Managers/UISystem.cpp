// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/UISystem.h"

#include "WOSGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "UI/LoginPopup.h"

void UUISystem::ShowPopup(FString Title, FString Content) const
{
	auto WOSGameMode = Cast<AWOSGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	auto Popup = Cast<ULoginPopup>(CreateWidget(GetWorld(), WOSGameMode->LoginPopup));
	if (Popup)
	{
		Popup->AddToViewport();
		Popup->SetTitle(FText::FromString(Title));
		Popup->SetContent(FText::FromString(Content));
	}
}
