// Fill out your copyright notice in the Description page of Project Settings.

#include "Manager.h"
#include "NetObjectManager.h"
#include "Managers/OnLevelLoadedEventCaller.h"

// Sets default values
AOnLevelLoadedEventCaller::AOnLevelLoadedEventCaller()
{

}

// Called when the game starts or when spawned
void AOnLevelLoadedEventCaller::BeginPlay()
{
	Super::BeginPlay();
	UManager::Object()->OnLevelLoaded();
}

