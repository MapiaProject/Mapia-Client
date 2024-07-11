// Fill out your copyright notice in the Description page of Project Settings.

#include "Managers/OnLevelLoadedEventCaller.h"
#include "Manager.h"
#include "NetObjectManager.h"

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

