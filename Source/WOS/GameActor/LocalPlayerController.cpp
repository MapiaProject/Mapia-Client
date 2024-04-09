// Fill out your copyright notice in the Description page of Project Settings.


#include "GameActor/LocalPlayerController.h"
#include "PlayerCharacter.h"
#include "Managers/Manager.h"
#include "Managers/Network.h"
#include "Network/generated/mmo/Protocol.gen.hpp"


void ALocalPlayerController::SetupInputComponent() {
	InputComponent->BindAxis(TEXT("Move"), this, &ALocalPlayerController::MoveHandler);
	InputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ALocalPlayerController::JumpHandler);
	InputComponent->BindAction(TEXT("Attack"), EInputEvent::IE_Pressed, this, &ALocalPlayerController::AttackHandler);
}

void ALocalPlayerController::MoveHandler(float Axis) {
	if (Axis != LastMoveInput) {
		LastMoveInput = Axis;

		gen::mmo::Move MovePacket;
		MovePacket.dir.x = Axis;
		UManager::Net()->Send(ServerType::MMO, &MovePacket);
	}
}

void ALocalPlayerController::JumpHandler() {

}

void ALocalPlayerController::AttackHandler() {

}