// Fill out your copyright notice in the Description page of Project Settings.


#include "GameActor/Player/GreatSword.h"

void UGreatSword::OnSwitchedFrom(TObjectPtr<UWeapon> Other)
{
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Magenta, TEXT("Great Sword"));
}
