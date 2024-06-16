// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameActor/Player/Weapon.h"
#include "Sword.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class WOS_API USword : public UWeapon
{
	GENERATED_BODY()
	
public:
	virtual void OnSwitchedFrom(TObjectPtr<UWeapon> Other);

private:
	UPROPERTY(EditAnywhere, Category = GreatSwordInfo)
		int MaxEnergy;
	UPROPERTY(EditAnywhere, Category = GreatSwordInfo)
		int EnergyRegenSpeed;

	UPROPERTY(EditAnywhere, Category = GreatSwordLightAttack)
		int LightAttackDamage;
	UPROPERTY(EditAnywhere, Category = GreatSwordLightAttack)
		float LightAttackAfterDelay;

	UPROPERTY(EditAnywhere, Category = GreatSwordHeavyAttack)
		int HeavyAttackDamage;
	UPROPERTY(EditAnywhere, Category = GreatSwordHeavyAttack)
		float HeavyAttackAfterDelay;
};
