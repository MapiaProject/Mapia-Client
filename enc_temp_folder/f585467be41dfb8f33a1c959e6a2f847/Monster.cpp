// Fill out your copyright notice in the Description page of Project Settings.


#include "GameActor/Monster/Monster.h"
#include "PaperFlipbookComponent.h"

void AMonster::BeginPlay() {
	GetSprite()->SetMaterial(0, DamagedMaterial);
	GetSprite()->SetFlipbook(IdleAnimation);
}

void AMonster::ReceivePacket(const Packet* ReadingPacket)
{
}

void AMonster::DestroyNetObject()
{
}

bool AMonster::TakeDamage(int Damage)
{
	return false;
}

