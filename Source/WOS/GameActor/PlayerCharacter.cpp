// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "PaperFlipbookComponent.h"
#include "Managers/Manager.h"
#include "Managers/Network.h"
#include "GameFramework/PlayerController.h"
#include "Camera/CameraComponent.h"
#include "Engine/LocalPlayer.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Util/NetUtility.h"
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
	ServerTimer += DeltaTime;
	LastInputTimer += DeltaTime;

	auto Position = Lerp(LastPosition, ServerPosition, ServerTimer / 0.2f) * 100;
	SetActorLocation(FVector(Position.X, Position.Y, 0));

	if (GetIsmine()) {
		if (time > LastSendPositionTime + sendPositionInterval) {
			LastSendPositionTime = time;

			SendMovePacket(ServerPosition.X + LastMoveInput, 0);
		}
	}

	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Magenta, FString::Printf(TEXT("(%d, %d)"), ServerPosition.X, ServerPosition.Y));
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);

	if (EnhancedInputComponent != nullptr) {
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::MoveHandler);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this, &APlayerCharacter::MoveHandler);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &APlayerCharacter::JumpHandler);
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Started, this, &APlayerCharacter::AttackHandler);
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("InputComponent is not EnhancedInputComponent"));
	}

	auto ControllerPtr = Cast<APlayerController>(GetController());
	if (ControllerPtr != nullptr) {
		if (auto SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(ControllerPtr->GetLocalPlayer())) {
			SubSystem->AddMappingContext(InputMappingContext, 0);
		}
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("PlayerCharacter Can't Found PlayerController"));
	}


	PrimaryActorTick.bCanEverTick = true;
}

void APlayerCharacter::SetName(FStringView SettedName) {
	Name = SettedName;
}

void APlayerCharacter::HandleSpawn(FVector2D Position)
{
	LastPosition = Position;
	ServerPosition = Position;
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
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("Handle Packet"));
	switch (ReadingPacket->GetId()) {
	case gen::mmo::PacketId::NOTIFY_MOVE:
		HandleMove(*static_cast<const gen::mmo::NotifyMove*>(ReadingPacket));
		break;
	}
}

void APlayerCharacter::HandleMove(gen::mmo::NotifyMove MovePacket) {
	LastPosition = ServerPosition;
	ServerPosition = FVector2D(MovePacket.position.x, MovePacket.position.y);
	ServerTimer = 0;
}

void APlayerCharacter::DestroyNetObject()
{
	Destroy();
}

void APlayerCharacter::MoveHandler(const FInputActionValue& Value) {
	float Axis = Value.Get<float>();
	if (Axis != LastMoveInput) {
		if (LastMoveInput == 0 && LastInputTimer > 0.2f) {
			LastInputTimer = 0;

			LastSendPositionTime = GetWorld()->GetTimeSeconds() - 0.2f;
		}

		LastMoveInput = Axis;

		if (LastMoveInput != 0) {
			GetSprite()->SetWorldScale3D(FVector(SpriteOriginScale.X * LastMoveInput, SpriteOriginScale.Y, SpriteOriginScale.Z));
			GetSprite()->SetFlipbook(WalkAnimation);
		}
		else {
			GetSprite()->SetFlipbook(IdleAnimation);
		}
	}
}

void APlayerCharacter::JumpHandler() {

}

void APlayerCharacter::AttackHandler() {
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Magenta, TEXT("Try Scan"));
	ScanHitbox(FVector2D(0, 0), FVector2D(500, 500));
}

void APlayerCharacter::SendMovePacket(float X, float Y) {
	gen::mmo::Move MovePacket;
	MovePacket.position.x = X;
	MovePacket.position.y = Y;

	UManager::Net()->Send(ServerType::MMO, &MovePacket);
}

float APlayerCharacter::Lerp(float a, float b, float t)
{
	return a + (b - a) * t;
}

FVector2D APlayerCharacter::Lerp(FVector2D a, FVector2D b, float t)
{
	return FVector2D(Lerp(a.X, b.X, t), Lerp(a.Y, b.Y, t));
}

TArray<NetObject> APlayerCharacter::ScanHitbox(FVector2D AddedPosition, FVector2D Scale)
{
	auto Pos = FVector(AddedPosition.X, AddedPosition.Y, 0);
	ETraceTypeQuery ObjectTypes = UEngineTypes::ConvertToTraceType(ECollisionChannel::ECC_WorldDynamic);
	TArray<AActor*> IgnoreActors;
	TArray<FHitResult> Result;

	UKismetSystemLibrary::BoxTraceMulti(GetWorld(), Pos, Pos, FVector(Scale.X, Scale.Y, 0), FRotator::ZeroRotator, ObjectTypes, false, IgnoreActors, EDrawDebugTrace::ForDuration, Result, true);

	TArray <NetObject> NetObjects = TArray<NetObject>();

	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Magenta, FString::Printf(TEXT("count : %d"), Result.Num()));

	return NetObjects;
}
