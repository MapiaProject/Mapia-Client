// Fill out your copyright notice in the Description page of Project Settings.


#include "GameActor/Monster/AttackDrone.h"

void AAttackDrone::BeginPlay()
{
	Super::BeginPlay();
}

void AAttackDrone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetName(TEXT("AttackDrone"));
}

void AAttackDrone::AirBorne()
{
	Super::AirBorne();
}