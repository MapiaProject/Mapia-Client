// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MHGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class MORALHAZARD_API AMHGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	AMHGameModeBase();
	virtual ~AMHGameModeBase() override;
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
