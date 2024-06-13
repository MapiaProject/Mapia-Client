// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameActor/Player/Weapon.h"
#include "PlayerCharacter.h"
#include "Gun.generated.h"

/**
 *
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class WOS_API UGun : public UWeapon
{
	GENERATED_BODY()

public:
	virtual void Init(TObjectPtr<APlayerCharacter> PlayerChracter) override;
	virtual void OnSwitchedFrom(TObjectPtr<UWeapon> Other)override;
	virtual void OnSwitchedTo(TObjectPtr<UWeapon> Other)override;
	virtual void LightAttackHandler(int Axis) override;
	virtual void HeavyAttackHandler(int Axis) override;
	virtual void Skill1Handler(int Axis) override;
	//virtual void ParryingHandler(int Axis) override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	float GetEnergy();

private:
	UPROPERTY(EditAnywhere, Category = GunInfo)
		int MaxEnergy;
	UPROPERTY(EditAnywhere, Category = GunLightAttack)
		int LightAttackDamage;
	UPROPERTY(EditAnywhere, Category = GunLightAttack)
		int LightAttackNeededEnergy;
	UPROPERTY(EditAnywhere, Category = GunLightAttack)
		float LightAttackCoolTime;
	UPROPERTY(EditAnywhere, Category = GunLightAttack)
		float LightAttackAfterDelay;
	UPROPERTY(EditAnywhere, Category = GunHeavyAttack)
		int HeavyAttackDamage;
	UPROPERTY(EditAnywhere, Category = GunHeavyAttack)
		int HeavyAttackNeededEnergy;
	UPROPERTY(EditAnywhere, Category = GunHeavyAttack)
		int HeavyAttackCount;
	UPROPERTY(EditAnywhere, Category = GunHeavyAttack)
		float HeavyAttackDelay;
	UPROPERTY(EditAnywhere, Category = GunHeavyAttack)
		float HeavyAttackAfterDelay;
	UPROPERTY(EditAnywhere, Category = Reroad)
		float ReloadCoolTime;
	UPROPERTY(EditAnywhere, Category = Reroad)
		float ReloadAfterDelay;

	float Energy;
	int HeavyAttackCounter;
	float HeavyAttackTimer;

	float LastLightAttackTime;
	float LastReloadTime;
};
