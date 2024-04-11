// Fill out your copyright notice in the Description page of Project Settings.


#include "GameActor/PlayableController.h"
#include "PlayerCharacter.h"
#include "Managers/Manager.h"
#include "Managers/Network.h"
#include "Network/generated/mmo/Protocol.gen.hpp"

APlayableController::APlayableController() {
	PrimaryActorTick.bCanEverTick = true;
}

void APlayableController::SetupInputComponent() {
	InputComponent->BindAxis(TEXT("Move"), this, &APlayableController::MoveHandler);
	InputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &APlayableController::JumpHandler);
	InputComponent->BindAction(TEXT("Attack"), EInputEvent::IE_Pressed, this, &APlayableController::AttackHandler);

	PrimaryActorTick.bCanEverTick = true;
}

void APlayableController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	float time = GetWorld()->GetTimeSeconds();

	if (time > LastSendPositionTime + sendPositionInterval) {
		LastSendPositionTime = time;

		gen::mmo::Move MovePacket;
		MovePacket.dir.x = LastMoveInput;
		UManager::Net()->Send(ServerType::MMO, &MovePacket);
	}
}
	
void APlayableController::MoveHandler(float Axis) {
	if (Axis != LastMoveInput) {
		LastMoveInput = Axis;

		gen::mmo::Move MovePacket;
		MovePacket.dir.x = Axis;
		UManager::Net()->Send(ServerType::MMO, &MovePacket);
	}
}

void APlayableController::JumpHandler() {

}

void APlayableController::AttackHandler() {

}