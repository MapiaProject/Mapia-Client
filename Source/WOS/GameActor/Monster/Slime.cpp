// Fill out your copyright notice in the Description page of Project Settings.


#include "GameActor/Monster/Slime.h"
#include "PaperFlipbookComponent.h"

void ASlime::BeginPlay()
{
	Super::BeginPlay();

	SetName(TEXT("Slime"));
}

void ASlime::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASlime::AirBorne()
{
	Super::AirBorne();
}
