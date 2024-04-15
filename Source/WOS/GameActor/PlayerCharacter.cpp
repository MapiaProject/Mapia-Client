// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Engine.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void APlayerCharacter::Move(float Axis) {
	UE_LOG(LogTemp, Log, TEXT("Axis : %f"), Axis);
}

void APlayerCharacter::Jump() {
	UE_LOG(LogTemp, Log, TEXT("Jump"));
}

void APlayerCharacter::Attack() {
	UE_LOG(LogTemp, Log, TEXT("Attack"));
}

void APlayerCharacter::SetName(FStringView SettedName) {
	Name = SettedName;
}

void APlayerCharacter::RecievePacket(const Packet* ReadingPacket) {

}