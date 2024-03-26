// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/UISystem.h"

#include "WOSGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "UI/LoginPopup.h"

void UUISystem::ShowPopup(UWorld* World, FString Title, FString Content)
{
	const auto WOSGameMode = Cast<AWOSGameModeBase>(UGameplayStatics::GetGameMode(World));
	if (auto Popup = Cast<ULoginPopup>(CreateWidget(World, WOSGameMode->LoginPopup)))
	{
		Popup->AddToViewport();
		Popup->SetTitle(FText::FromString(Title));
		Popup->SetContent(FText::FromString(Content));
	}
}
