// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../NetObject.h"
#include "PaperFlipbook.h"
#include "PaperCharacter.h"
#include "Network/generated/mmo/Protocol.gen.hpp"
#include "Monster.generated.h"

/**
 *
 */
UCLASS()
class WOS_API AMonster : public APaperCharacter, public NetObject
{
	GENERATED_BODY()

public:
	AMonster();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere, Category = MonsterInfo)
	FString Name;

	UPROPERTY(EditAnywhere, Category = Animation)
	TObjectPtr<UPaperFlipbook> IdleAnimation;
	UPROPERTY(EditAnywhere, Category = Animation)
	TObjectPtr<UPaperFlipbook> WalkAnimation;
	UPROPERTY(EditAnywhere, Category = Animation)
	TObjectPtr<UPaperFlipbook> AttackAnimation;
	UPROPERTY(EditAnywhere, Category = Animation)
	TObjectPtr<UPaperFlipbook> AirborneAnimation;
	UPROPERTY(EditAnywhere, Category = Animation)
	TObjectPtr<UPaperFlipbook> DieAnimation;
	UPROPERTY(EditAnywhere, Category = Animation)
	float AttackAnimationTime;
	UPROPERTY(EditAnywhere, Category = Animation)
	float AirBorneAnimationTime;

	UPROPERTY(EditAnywhere, Category = Material)
	TObjectPtr<UMaterialInterface> DefaultMaterial;
	UPROPERTY(EditAnywhere, Category = Material)
	TObjectPtr<UMaterialInterface> DamagedMaterial;
	UPROPERTY(EditAnywhere, Category = Material)
	float MaxDamageEffectTime;

	UPROPERTY(VisibleAnywhere)
	class UWidgetComponent* MonsterInfoUI;

	virtual void ReceivePacket(const Packet* ReadingPacket) override;
	virtual bool TakeDamage(int Damage) override;
	virtual void DestroyNetObject() override;

	void SetSpawnPos(FVector2D Pos);

protected:
	void ReceiveNotifyMove(gen::mmo::NotifyMove MovePacket);
	void SetName();
	void SetHP();
	void Attack();
	void Move();
	void AirBorne();

	float Lerp(float a, float b, float t);
	FVector2D Lerp(FVector2D a, FVector2D b, float t);

	float MaxHP;
	float CurHP;

	bool DamageEffectOn;
	float CurDamageEffectTime;

	int Dir;
	FVector2D StartPos;
	FVector2D DestinationPos;
	float MoveTimer;

	float AttackAnimationTimer;
	float AirBorneAnimationTimer;

	bool isAttack;
	bool isAirBorne;

	float AirBornePower;
	float DeltaTimeCopy;
	float Difference;
	int RepeatCnt;

};