// Fill out your copyright notice in the Description page of Project Settings.


#include "GameActor/Player/Weapon.h"
#include "PlayerCharacter.h"

// Sets default values for this component's properties
UWeapon::UWeapon()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UWeapon::Init(TObjectPtr<APlayerCharacter> PlayerChracter)
{
	this->Owner = Owner;
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Magenta, TEXT("Init"));
}

void UWeapon::OnSwitchedFrom(TObjectPtr<UWeapon> Other)
{
}

void UWeapon::OnSwitchedTo(TObjectPtr<UWeapon> Other)
{
}

void UWeapon::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
}

void UWeapon::LightAttackHandler(int Axis)
{
}

void UWeapon::HeavyAttackHandler(int Axis)
{
}

void UWeapon::ParryingHandler(int Axis)
{
}

bool UWeapon::IsUsing()
{
	return Owner->CurrentWeapon == this;
}

FString UWeapon::GetName()
{
	return Name;
}
