// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Weapon.generated.h"

class APlayerCharacter;


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

protected:
	UPROPERTY(EditAnywhere, Category = Info)
		FString Name;

	bool IsUsing();

	TObjectPtr<APlayerCharacter> Owner;

public:
	FString GetName();
};
