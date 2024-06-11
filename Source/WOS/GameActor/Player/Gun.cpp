// Fill out your copyright notice in the Description page of Project Settings.


#include "GameActor/Player/Gun.h"

void UGun::OnSwitchedFrom(TObjectPtr<UWeapon> Other)
{
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Magenta, TEXT("Gun"));
}

void UGun::LightAttackHandler(int Axis)
{
	Owner->ScanHitbox(FVector2d(50, 0), FVector2D(1000, 100));
}
