// Fill out your copyright notice in the Description page of Project Settings.


#include "GameActor/Player/Gun.h"

void UGun::Init(TObjectPtr<APlayerCharacter> PlayerChracter)
{
	Super::Init(PlayerChracter);
	Energy = MaxEnergy;
}

void UGun::OnSwitchedFrom(TObjectPtr<UWeapon> Other)
{
	Super::OnSwitchedFrom(Other);
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Magenta, TEXT("Gun"));
}

void UGun::OnSwitchedTo(TObjectPtr<UWeapon> Other)
{
	HeavyAttackCount = 0;
}

void UGun::LightAttackHandler(int Axis)
{
	Super::LightAttackHandler(Axis);
	if (CHECK_COOLTIME(LightAttack) && Energy >= LightAttackNeededEnergy) {
		LastLightAttackTime = GetWorld()->TimeSeconds;
		Energy -= LightAttackNeededEnergy;
		int a = SendDamage(ScanHitbox(FVector2D(50, 0), FVector2D(1000, 100)), LightAttackDamage);
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Magenta, FString::Printf(TEXT("targetCount : %d"), a));
	}
}

void UGun::HeavyAttackHandler(int Axis)
{
	Super::HeavyAttackHandler(Axis);
	if (Energy >= HeavyAttackNeededEnergy) {
		Energy -= HeavyAttackNeededEnergy;
		HeavyAttackCounter = HeavyAttackCount;
		HeavyAttackTimer = 0;
	}
}

void UGun::Skill1Handler(int Axis)
{
	Super::Skill1Handler(Axis);
	if (Energy < 100 && CHECK_COOLTIME(Reload)) {
		LastReloadTime = GetWorld()->TimeSeconds;
		Energy = MaxEnergy;
	}
}

void UGun::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (IsUsing() && HeavyAttackCounter > 0) {
		HeavyAttackTimer += DeltaTime;

		if (HeavyAttackTimer > HeavyAttackDelay) {
			HeavyAttackCounter--;
			HeavyAttackTimer = 0;
			SendDamage(ScanHitbox(FVector2D(50, 0), FVector2D(1000, 100)), HeavyAttackDamage);
		}
	}
}

float UGun::GetEnergy()
{
	return Energy;
}
