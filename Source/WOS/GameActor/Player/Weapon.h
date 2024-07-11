// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Weapon.generated.h"

class APlayerCharacter;

#define CHECK_COOLTIME(SkillName) Last##SkillName##Time + SkillName##CoolTime >= GetWorld()->TimeSeconds


UCLASS()
class WOS_API UWeapon : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UWeapon();
	
	virtual void Init(TObjectPtr<APlayerCharacter> PlayerCharacter);
	virtual void OnSwitchedFrom(TObjectPtr<UWeapon> Other);
	virtual void OnSwitchedTo(TObjectPtr<UWeapon> Other);
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction);

	virtual void LightAttackHandler(int Axis);
	virtual void HeavyAttackHandler(int Axis);
	virtual void ParryingHandler(int Axis);
	virtual void Skill1Handler(int Axis);
	virtual void Skill2Handler(int Axis);
	virtual void Skill3Handler(int Axis);

protected:
	UPROPERTY(EditAnywhere, Category = Info)
		FString Name;

	bool IsUsing();
	TArray<AActor*> ScanHitbox(FVector2D AddedPosition, FVector2D Scale, float Dir = 0, bool IgnoreFlip = false);
	bool SendDamage(AActor* Target,int Damage);
	int SendDamage(TArray<AActor*> Target,int Damage);
	void SetAfterDelay(float Delay);
	bool IsAfterDelaying();
	void Dash(int Direction);
	int GetLastMoveInput();
	void MoveAnimationLogic(int Axis);
	void Parrying(float Time);

	TObjectPtr<APlayerCharacter> Owner;

public:
	FString GetName();
};
