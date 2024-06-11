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
};
