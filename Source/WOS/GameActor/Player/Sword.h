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
	virtual void Init(TObjectPtr<APlayerCharacter> PlayerCharacter);
	virtual void OnSwitchedFrom(TObjectPtr<UWeapon> Other);
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction);

	virtual void LightAttackHandler(int Axis);
	virtual void HeavyAttackHandler(int Axis);
	//virtual void Skill2Handler(int Axis);
	//virtual void Skill3Handler(int Axis);

	float GetEnergy();

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

	UPROPERTY(EditAnywhere, Category = Rush)
		int RushDamage;
	UPROPERTY(EditAnywhere, Category = Rush)
		int RushNeededEnergy;
	UPROPERTY(EditAnywhere, Category = Rush)
		float RushCoolTime;
	UPROPERTY(EditAnywhere, Category = Rush)
		float RushAfterDelay;
	UPROPERTY(EditAnywhere, Category = Rush)
		float RushLength;

	UPROPERTY(EditAnywhere, Category = BackStep)
		int BackStepDamage;
	UPROPERTY(EditAnywhere, Category = BackStep)
		int BackStepNeededEnergy;
	UPROPERTY(EditAnywhere, Category = BackStep)
		float BackStepCoolTime;
	UPROPERTY(EditAnywhere, Category = BackStep)
		float BackStepAfterDelay;
	UPROPERTY(EditAnywhere, Category = BackStep)
		float BackStepLength;

	float Energy;

	float LastAirBoneTime;
	float LastRushTime;
	float LastBackStepTime;
};
