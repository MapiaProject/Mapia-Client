// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperSpriteActor.h"
#include "NetObject.h"
#include "Network/generated/mmo/Protocol.gen.hpp"
#include "Projectile.generated.h"

/**
 * 
 */
UCLASS()
class WOS_API AProjectile : public APaperSpriteActor, public NetObject
{
	GENERATED_BODY()
	
public:
	void Tick(float DeltaTime);

	virtual void ReceivePacket(const Packet* ReadingPacket) override;
	virtual bool TakeDamage(int Damage) override;
	virtual void DestroyNetObject() override;

private:
	void ReceiveNotifyMove(gen::mmo::NotifyMove MovePacket);
	void Move();

	float Lerp(float a, float b, float t);
	FVector2D Lerp(FVector2D a, FVector2D b, float t);

	int Dir;
	FVector2D StartPos;
	FVector2D DestinationPos;
	float MoveTimer;

};
