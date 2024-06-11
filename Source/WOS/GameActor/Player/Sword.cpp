// Fill out your copyright notice in the Description page of Project Settings.


#include "GameActor/Player/Sword.h"

void USword::OnSwitchedFrom(TObjectPtr<UWeapon> Other)
{
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Magenta, TEXT("Sword"));
}
