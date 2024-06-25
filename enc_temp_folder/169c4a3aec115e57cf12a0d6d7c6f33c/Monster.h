// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../NetObject.h"
#include "PaperFlipbook.h"
#include "PaperCharacter.h"
#include "Monster.generated.h"

/**
 * 
 */
UCLASS()
class WOS_API AMonster : public APaperCharacter, public NetObject
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

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

	UPROPERTY(EditAnywhere, Category=Material)
	TObjectPtr<UMaterialInterface> DefaultMaterial;
	UPROPERTY(EditAnywhere, Category=Material)
	TObjectPtr<UMaterialInterface> DamagedMaterial;

	virtual void ReceivePacket(const Packet* ReadingPacket) override;
	virtual void DestroyNetObject() override;
	virtual bool TakeDamage(int Damage) override;
};
