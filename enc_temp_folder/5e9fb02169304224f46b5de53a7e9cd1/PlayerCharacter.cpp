// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "PaperFlipbookComponent.h"
#include "Managers/Manager.h"
#include "Managers/Network.h"
#include "GameFramework/PlayerController.h"
#include "Camera/CameraComponent.h"
#include "Engine/LocalPlayer.h"
#include "Network/generated/mmo/Packet.gen.hpp"
//#include "Engine.h"

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

	GetSprite()->SetFlipbook(IdleAnimation);
	SpriteOriginScale = GetSprite()->GetComponentScale();
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	float time = GetWorld()->GetTimeSeconds();

	if (GetIsmine()) {
		auto p = GetActorLocation();
		SetActorLocation(p + FVector(DeltaTime * LastMoveInput * MoveSpeed / 0.2f, 0, 0));

		if (time > LastSendPositionTime + sendPositionInterval) {
			LastSendPositionTime = time;

			SendMovePacket(LastMoveInput, 0);
		}
	}
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (GetIsmine()) {
		UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);

		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::MoveHandler);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this, &APlayerCharacter::MoveHandler);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &APlayerCharacter::JumpHandler);
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Started, this, &APlayerCharacter::AttackHandler);

		auto ControllerPtr = Cast<APlayerController>(GetController());
		if (ControllerPtr != nullptr) {
			if (auto SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(ControllerPtr->GetLocalPlayer())) {
				SubSystem->AddMappingContext(InputMappingContext, 0);
			}
		}
		else {
			UE_LOG(LogTemp, Error, TEXT("LocalPlayerCharacter Can't Found PlayerController"));
		}
	}

	PrimaryActorTick.bCanEverTick = true;
}

void APlayerCharacter::SetName(FStringView SettedName) {
	Name = SettedName;
}

void APlayerCharacter::SetIsmine()
{
	bIsmine = true;
}

bool APlayerCharacter::GetIsmine()
{
	return bIsmine;
}

void APlayerCharacter::RecievePacket(const Packet* ReadingPacket) {
	switch (ReadingPacket->GetId()) {
	case gen::mmo::PacketId::NOTIFY_MOVE:
		HandleMove(*static_cast<const gen::mmo::NotifyMove*>(ReadingPacket));
		break;
	}
}

void APlayerCharacter::HandleMove(gen::mmo::NotifyMove MovePacket) {

}

void APlayerCharacter::DestroyNetObject()
{
	Destroy();
}

void APlayerCharacter::MoveHandler(const FInputActionValue& Value) {

	float Axis = Value.Get<float>();
	if (Axis != LastMoveInput) {
		LastMoveInput = Axis;

		LastSendPositionTime = GetWorld()->GetTimeSeconds();

		if (LastMoveInput != 0) {
			GetSprite()->SetWorldScale3D(FVector(SpriteOriginScale.X * LastMoveInput, SpriteOriginScale.Y, SpriteOriginScale.Z));
			GetSprite()->SetFlipbook(WalkAnimation);
		}
		else {
			GetSprite()->SetFlipbook(IdleAnimation);
		}

		SendMovePacket(Axis, 0);
	}
}

void APlayerCharacter::JumpHandler() {

}

void APlayerCharacter::AttackHandler() {

}

void APlayerCharacter::SendMovePacket(float X, float Y) {
	gen::mmo::Move MovePacket;
	MovePacket.position.x = X;
	MovePacket.position.y = Y;
	//UManager::Net()->Send(ServerType::MMO, &MovePacket);
}