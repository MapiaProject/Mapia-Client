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
	virtual void Init(TObjectPtr<APlayerCharacter> PlayerCharacter) override;
	virtual void OnSwitchedFrom(TObjectPtr<UWeapon> Other) override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void LightAttackHandler(int Axis) override;
	virtual void HeavyAttackHandler(int Axis) override;
	virtual void ParryingHandler(int Axis) override;
	virtual void Skill2Handler(int Axis) override;
	virtual void Skill3Handler(int Axis) override;

	float GetEnergy();

private:
	UPROPERTY(EditAnywhere, Category = SwordInfo)
	int MaxEnergy;
	UPROPERTY(EditAnywhere, Category = SwordInfo)
	int EnergyRegenSpeed;

	UPROPERTY(EditAnywhere, Category = SwordLightAttack)
	int LightAttackDamage;
	UPROPERTY(EditAnywhere, Category = SwordLightAttack)
	float LightAttackAfterDelay;

	UPROPERTY(EditAnywhere, Category = SwordHeavyAttack)
	int HeavyAttackDamage;
	UPROPERTY(EditAnywhere, Category = SwordHeavyAttack)
	float HeavyAttackAfterDelay;

	UPROPERTY(EditAnywhere, Category = SwordParrying)
	float ParryingTime;

	UPROPERTY(EditAnywhere, Category = SwordRush)
	int RushDamage;
	UPROPERTY(EditAnywhere, Category = SwordRush)
	int RushNeededEnergy;
	UPROPERTY(EditAnywhere, Category = SwordRush)
	float RushCoolTime;
	UPROPERTY(EditAnywhere, Category = SwordRush)
	float RushAfterDelay;
	UPROPERTY(EditAnywhere, Category = SwordRush)
	float RushLength;

	UPROPERTY(EditAnywhere, Category = SwordBackStep)
	int BackStepDamage;
	UPROPERTY(EditAnywhere, Category = SwordBackStep)
	int BackStepNeededEnergy;
	UPROPERTY(EditAnywhere, Category = SwordBackStep)
	float BackStepCoolTime;
	UPROPERTY(EditAnywhere, Category = SwordBackStep)
	float BackStepAfterDelay;
	UPROPERTY(EditAnywhere, Category = SwordBackStep)
	float BackStepLength;

	float Energy;

	float LastAirBoneTime;
	float LastRushTime;
	float LastBackStepTime;
};
