// Fill out your copyright notice in the Description page of Project Settings.


#include "GameFramework/PlayerController.h"
#include "Managers/Manager.h"
#include "Managers/Network.h"
#include "GameActor/LocalPlayerCharacter.h"
#include "Engine/LocalPlayer.h"

void ALocalPlayerCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);

	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ALocalPlayerCharacter::MoveHandler);
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this, &ALocalPlayerCharacter::MoveHandler);
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ALocalPlayerCharacter::JumpHandler);
	InputComponent->BindAction(TEXT("Attack"), EInputEvent::IE_Pressed, this, &ALocalPlayerCharacter::AttackHandler);

	PrimaryActorTick.bCanEverTick = true;
}

void ALocalPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	auto ControllerPtr = Cast<APlayerController>(Controller);
	if (Controller != nullptr) {
		if (auto SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(ControllerPtr->GetLocalPlayer())) {
			SubSystem->AddMappingContext(InputMappingContext, 0);
		}
	}
}

void ALocalPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	float time = GetWorld()->GetTimeSeconds();

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

	UE_LOG(LogTemp, Log, TEXT("(%f, %f)"),X,Y);
}

void ALocalPlayerCharacter::JumpHandler() {
}

void ALocalPlayerCharacter::AttackHandler() {
}