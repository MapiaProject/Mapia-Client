// Fill out your copyright notice in the Description page of Project Settings.


#include "GameActor/LocalPlayerCharacter.h"
#include "GameFramework/PlayerController.h"
#include "Managers/Manager.h"
#include "Managers/Network.h"
#include "Engine/LocalPlayer.h"

void ALocalPlayerCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);

	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ALocalPlayerCharacter::MoveHandler);
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this, &ALocalPlayerCharacter::MoveHandler);
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ALocalPlayerCharacter::JumpHandler);
	EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Started, this, &ALocalPlayerCharacter::AttackHandler);

	auto ControllerPtr = Cast<APlayerController>(GetController());
	if (ControllerPtr != nullptr) {
		if (auto SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(ControllerPtr->GetLocalPlayer())) {
			SubSystem->AddMappingContext(InputMappingContext, 0);
		}
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("LocalPlayerCharacter Can't Found PlayerController"));
	}

	PrimaryActorTick.bCanEverTick = true;
}

void ALocalPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ALocalPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	float time = GetWorld()->GetTimeSeconds();

	auto p = GetActorLocation();
	SetActorLocation(p + FVector(DeltaTime * LastMoveInput, 0, 0));

	if (time > LastSendPositionTime + sendPositionInterval) {
		LastSendPositionTime = time;

		SendMovePacket(LastMoveInput, 0);
	}
}

void ALocalPlayerCharacter::MoveHandler(const FInputActionValue& Value) {

	float Axis = Value.Get<float>();
	if (Axis != LastMoveInput) {
		LastMoveInput = Axis;

		LastSendPositionTime = GetWorld()->GetTimeSeconds();

		SendMovePacket(Axis, 0);
	}
}

void ALocalPlayerCharacter::SendMovePacket(float X, float Y) {
	gen::mmo::Move MovePacket;
	MovePacket.dir.x = X;
	MovePacket.dir.y = Y;
	UManager::Net()->Send(ServerType::MMO, &MovePacket);
}

void ALocalPlayerCharacter::JumpHandler() {

}

void ALocalPlayerCharacter::AttackHandler() {

}