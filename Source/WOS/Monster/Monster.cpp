// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/Monster.h"

// Sets default values
AMonster::AMonster()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMonster::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector curPos = GetActorLocation();
	SetActorLocation(FVector(FVector2D(FMath::FInterpConstantTo(curPos.X, targetPos, DeltaTime, 1), curPos.Y), curPos.Z));
}

void AMonster::RecievePacket(const Packet* packet) {
	switch (packet->GetId()) {
	// 몇으로 할지 모름
	case 1:
		MoveHandler(static_cast<const /*MonsterMove*/Packet*>(packet));
		break;
	case 2:
		SpawnHandler(static_cast<const /*SpawnMonster*/Packet*>(packet));
		break;
	case 3:
		
	}
}

void AMonster::MoveHandler(const /*MonsterMove*/Packet* packet) {
	// targetPos = Vector의 X좌표
}

void AMonster::SpawnHandler(const /*SpawnMonster*/Packet* packet) {
	// SetActorLocation(받은 위치)
}

void AMonster::AttackHandler(const /*SAddDamage*/Packet* packet) {

}