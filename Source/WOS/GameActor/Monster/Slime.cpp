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

	AttackTest += DeltaTime;
	if (AttackTest >= 10) {
		Attack();
		AttackTest = 0;
		UE_LOG(LogTemp, Warning, TEXT("Attack!"));
		isAttack = true;
	}
}

void ASlime::AirBorne()
{
	Super::AirBorne();
}
