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

void UWeapon::Init(TObjectPtr<APlayerCharacter> PlayerCharacter)
{
	this->Owner = PlayerCharacter;
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

void UWeapon::Skill1Handler(int Axis)
{
}

void UWeapon::Skill2Handler(int Axis)
{
}

void UWeapon::Skill3Handler(int Axis)
{
}

bool UWeapon::IsUsing()
{
	return Owner->CurrentWeapon == this;
}

TArray<AActor*> UWeapon::ScanHitbox(FVector2D AddedPosition, FVector2D Scale, float Dir, bool IgnoreFlip)
{
	return Owner->ScanHitbox(AddedPosition, Scale, Dir, IgnoreFlip);
}

bool UWeapon::SendDamage(AActor* Target, int Damage)
{
	NetObject* O = reinterpret_cast<NetObject*>(Target);
	if (O != nullptr) {
		return O->TakeDamage(Damage);
	}

	return false;
}

int UWeapon::SendDamage(TArray<AActor*> Target, int Damage)
{
	int Count = 0;
	for (auto T : Target) {
		if (SendDamage(T, Damage)) {
			Count++;
		}
	}
	return Count;
}

void UWeapon::SetAfterDelay(float Delay)
{
	Owner->SetAfterDelay(Delay);
}

bool UWeapon::IsAfterDelaying()
{
	return Owner->IsAfterDelaying();
}

FString UWeapon::GetName()
{
	return Name;
}
