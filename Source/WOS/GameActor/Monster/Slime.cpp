// Fill out your copyright notice in the Description page of Project Settings.


#include "GameActor/Monster/Slime.h"
#include "PaperFlipbookComponent.h"

void ASlime::BeginPlay()
{
	Super::BeginPlay();

}

void ASlime::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SetName(TEXT("Slime"));
	//SetHP(0, 0);
}

void ASlime::AirBorne()
{
	Super::AirBorne();
}