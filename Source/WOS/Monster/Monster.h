// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Network/Packet.h"
#include "../GameActor/NetObject.h"
#include "Math/UnrealMathUtility.h"

#include "Monster.generated.h"

UCLASS()
class WOS_API AMonster : public AActor, public NetObject
{
	GENERATED_BODY()
	
public:	
	AMonster();
	virtual void Tick(float DeltaTime) override;
	/*이거 ReceivePacket으로 바꿔야함*/ virtual void RecievePacket(const Packet* packet) override;
	virtual void MoveHandler(const /*MonsterMove*/Packet* packet);
	virtual void SpawnHandler(const /*SpawnMonster*/Packet* packet);
	virtual void AttackHandler(const /*SAddDamage*/Packet* packet);

protected:
	virtual void BeginPlay() override;

private:
	float targetPos;
};
