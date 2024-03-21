// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "WOSGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class WOS_API AWOSGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	AWOSGameModeBase();
	virtual ~AWOSGameModeBase() override;
public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
public:
	UPROPERTY()
	TSubclassOf<UUserWidget> TitleUIClass;
	UPROPERTY()
	TSubclassOf<UUserWidget> LobbyUIClass;
	UPROPERTY()
	UUserWidget* CurrentWidget;
};
