// Fill out your copyright notice in the Description page of Project Settings.


#include "GameActor/Monster/TurretPlant.h"

void ATurretPlant::BeginPlay()
{
	Super::BeginPlay();
}

void ATurretPlant::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetName(TEXT("TurretPlant"));
}

void ATurretPlant::AirBorne()
{
	Super::AirBorne();
}
