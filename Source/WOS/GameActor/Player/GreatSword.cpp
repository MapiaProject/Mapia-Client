// Fill out your copyright notice in the Description page of Project Settings.


#include "GameActor/Player/GreatSword.h"
#include "rpc.h"

void UGreatSword::Init(TObjectPtr<APlayerCharacter> PlayerCharacter)
{
	Super::Init(PlayerCharacter);
	Energy = MaxEnergy;
}

void UGreatSword::OnSwitchedFrom(TObjectPtr<UWeapon> Other)
{
	Super::OnSwitchedFrom(Other);
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Magenta, TEXT("Great Sword"));
}

void UGreatSword::OnSwitchedTo(TObjectPtr<UWeapon> Other)
{
	Super::OnSwitchedFrom(Other);
	OverflowTimer = 0;
}

void UGreatSword::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	Energy += DeltaTime * EnergyRegenSpeed;
	if (Energy > MaxEnergy) {
		Energy = MaxEnergy;
	}

	if (OverflowTimer > 0) {
		OverflowTimer -= DeltaTime;
	}
}

void UGreatSword::LightAttackHandler(int Axis)
{
	Super::LightAttackHandler(Axis);
	if (!IsAfterDelaying())
	{
		if (IsOverflow()) {
			SetAfterDelay(LightAttackAfterDelay / 2);
		}
		else {
			SetAfterDelay(LightAttackAfterDelay);
		}
		SendDamage(ScanHitbox(FVector2D(50, 0), FVector2D(200, 150)), LightAttackDamage);
	}
}

void UGreatSword::HeavyAttackHandler(int Axis)
{
	Super::HeavyAttackHandler(Axis);
	if (!IsAfterDelaying())
	{
		if (IsOverflow()) {
			SetAfterDelay(HeavyAttackAfterDelay / 2);
		}
		else {
			SetAfterDelay(HeavyAttackAfterDelay);
		}
		SendDamage(ScanHitbox(FVector2D(50, 0), FVector2D(300, 150)), HeavyAttackDamage);
	}
}

void UGreatSword::Skill1Handler(int Axis)
{
	Super::Skill1Handler(Axis);
	if (!IsAfterDelaying() && CHECK_COOLTIME(VerticalSmash))
	{
		SetAfterDelay(VerticalSmashAfterDelay);
		LastVerticalSmashTime = GetWorld()->TimeSeconds;
		int a = SendDamage(ScanHitbox(FVector2D(50, -100), FVector2D(200, 600)), VerticalSmashDamage);
		Owner->RPCJump(1);
	}
}

void UGreatSword::Skill2Handler(int Axis)
{
	Super::Skill2Handler(Axis);
	if (OverflowTimer < 0)
		OverflowTimer = OverflowTime;
}

float UGreatSword::GetEnergy()
{
	return Energy;
}

bool UGreatSword::IsOverflow()
{
	return GetOverflowRemainingTime() > 0;
}

float UGreatSword::GetOverflowRemainingTime()
{
	return OverflowTimer;
}

void UGreatSword::VerticalSmashAnimationLogic()
{

}
