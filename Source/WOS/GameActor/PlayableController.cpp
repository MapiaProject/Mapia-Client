// Fill out your copyright notice in the Description page of Project Settings.


#include "GameActor/PlayableController.h"
#include "PlayerCharacter.h"
#include "Managers/Manager.h"
#include "Managers/Network.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "Network/generated/mmo/Protocol.gen.hpp"

APlayableController::APlayableController() {
	PrimaryActorTick.bCanEverTick = true;
}

void APlayableController::SetupInputComponent() {
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);

	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayableController::MoveHandler);
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this, &APlayableController::MoveHandler);
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &APlayableController::JumpHandler);
	InputComponent->BindAction(TEXT("Attack"), EInputEvent::IE_Pressed, this, &APlayableController::AttackHandler);

	PrimaryActorTick.bCanEverTick = true;
}

void APlayableController::BeginPlay() {
	Super::BeginPlay();

	if (auto SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer())) {
		SubSystem->AddMappingContext(InputMappingContext, 0);
	}
}

void APlayableController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	float time = GetWorld()->GetTimeSeconds();

	if (time > LastSendPositionTime + sendPositionInterval) {
		LastSendPositionTime = time;

		SendMovePacket(LastMoveInput, 0);
	}
}

void APlayableController::SendMovePacket(float X, float Y) {
	gen::mmo::Move MovePacket;
	MovePacket.dir.x = X;
	MovePacket.dir.y = Y;
	UManager::Net()->Send(ServerType::MMO, &MovePacket);
}

void APlayableController::MoveHandler(const FInputActionValue& Value) {

	float Axis = Value.Get<float>();
	if (Axis != LastMoveInput) {
		LastMoveInput = Axis;

		LastSendPositionTime = GetWorld()->GetTimeSeconds();

		SendMovePacket(Axis, 0);
	}
}

void APlayableController::JumpHandler() {
}

void APlayableController::AttackHandler() {
}