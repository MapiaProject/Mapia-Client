// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "PaperFlipbookComponent.h"
#include "Managers/Manager.h"
#include "Managers/Network.h"
#include "GameFramework/PlayerController.h"
#include "Engine/LocalPlayer.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Util/NetUtility.h"
#include "Network/generated/mmo/Packet.gen.hpp"

#define DebugLog(x) GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Magenta, x);

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RPC(JumpAnimationLogic);
	RPC(FarryingAnimationLogic);
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	GetSprite()->SetFlipbook(IdleAnimation);
	SpriteOriginScale = GetSprite()->GetComponentScale();

	for (auto WeaponType : StartingWeapon) {
		MyWeapons.Add(static_cast<UWeapon*>(this->FindComponentByClass(WeaponType)));
	}

	for (auto Weapon : MyWeapons) {
		Weapon->Init(this);
	}
	if (MyWeapons.Num() > 0) {
		SwitchWeapon(0);
	}
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	float time = GetWorld()->GetTimeSeconds();
	ServerTimer += DeltaTime;
	LastInputTimer += DeltaTime;
	JumpAnimationTimer += DeltaTime;
	WeaponAfterDelay -= DeltaTime;
	DamagedMaterialTimer -= DeltaTime;
	ParryingTimer -= DeltaTime;

	auto MapData = UManager::Object()->GetCurrentMapData();

	//점프,낙하 애니메이션
	float jumpAnimationTime = 0.4f;
	float z;
	if (IsJumping) {
		z = Lerp(Lerp(JumpAnimationStartZ, JumpAnimationTop, JumpAnimationTimer / jumpAnimationTime), JumpAnimationTop, JumpAnimationTimer / jumpAnimationTime);
		//Log(FString::Printf(TEXT("(%f)"), JumpAnimationTop));

		if (JumpAnimationTimer > jumpAnimationTime) {
			IsJumping = false;
			int Bottom = MapData->GroundCast(Vector2Int(ServerPosition.X + LastMoveInput, LocalPositionY));

			LocalPositionY = Bottom;
			FallAnimationLogic(LocalPositionY);
		}
	}
	else if (IsFalling) {
		z = Lerp(JumpAnimationTop, Lerp(JumpAnimationTop, JumpAnimationBottom, JumpAnimationTimer / jumpAnimationTime), JumpAnimationTimer / jumpAnimationTime);

		if (JumpAnimationTimer > jumpAnimationTime) {
			IsFalling = false;
			MoveAnimationLogic(LastMoveAnimationValue);
		}
	}
	else {
		z = JumpAnimationBottom;
	}
	if (IsDamagedMaterialOn && DamagedMaterialTimer < 0) {
		GetSprite()->SetMaterial(0, DefaultMaterial);
		IsDamagedMaterialOn = false;
	}

	//위치 보간
	SetActorLocation(FVector(LocalPositionX * 100, 0, z));

	if (GetIsmine()) {
		//0.2초마다 자유낙하 계산, 위치 패킷 보내기
		FVector2D TargetPosition = MapData->RayCast(FVector2D(LocalPositionX, LocalPositionY), Vector2Int(LastMoveInput, 0), DeltaTime * MoveSpeed);
		MoveAnimationLogic(TargetPosition.X - LocalPositionX);
		LocalPositionX = TargetPosition.X;

		if (time > LastSendPositionTime + sendPositionInterval) {
			LastSendPositionTime = time;

			MoveLogic(FVector2D(LocalPositionX, LocalPositionY));
		}
	}
	if (!GetIsmine()) {
		float dir = ServerPosition.X - LastPosition.X;
		MoveAnimationLogic(dir);
	}
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);

	if (EnhancedInputComponent != nullptr) {
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::MoveInputHandler);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this, &APlayerCharacter::MoveInputHandler);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &APlayerCharacter::JumpInputHandler);
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Started, this, &APlayerCharacter::AttackInputHandler);
		EnhancedInputComponent->BindAction(ParryingAction, ETriggerEvent::Started, this, &APlayerCharacter::ParryingInputHandler);
		EnhancedInputComponent->BindAction(WeaponSwitchAction, ETriggerEvent::Started, this, &APlayerCharacter::WeaponSwitchInputHandler);
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
	LocalPositionY = Position.Y;
	LocalPositionX = Position.X;
	LastPosition = Position;
	ServerPosition = Position;
}

void APlayerCharacter::SetIsmine()
{
	bNetObjectIsmine = true;
}

bool APlayerCharacter::GetIsmine()
{
	return bNetObjectIsmine;
}

void APlayerCharacter::ReceivePacket(const Packet* ReadingPacket) {
	NetObject::ReceivePacket(ReadingPacket);
	switch (ReadingPacket->GetId()) {
	case gen::mmo::PacketId::NOTIFY_MOVE:
		ReceiveNotifyMove(*static_cast<const gen::mmo::NotifyMove*>(ReadingPacket));
		break;
	case gen::mmo::PacketId::NOTIFY_DAMAGED:
		ReceiveNotifyDamaged(*static_cast<const gen::mmo::NotifyDamaged*>(ReadingPacket));
		break;
	case gen::mmo::PacketId::TAKE_ATTACK:
		ReceiveTakeAttack(*static_cast<const gen::mmo::TakeAttack*>(ReadingPacket));
		break;
	}
}

void APlayerCharacter::ReceiveNotifyMove(gen::mmo::NotifyMove MovePacket) {

	LastPosition = ServerPosition;
	ServerPosition = FVector2D(MovePacket.position.x, MovePacket.position.y);
	ServerTimer = 0;

	LocalPositionY = ServerPosition.Y;

	if (!IsJumping) {
		auto MapData = UManager::Object()->GetCurrentMapData();
		int Bottom = MapData->GroundCast(Vector2Int(ServerPosition.X, LocalPositionY));
		if (Bottom < LocalPositionY) {
			if (LocalPositionY > Bottom) {
				LocalPositionY = Bottom;
				FallAnimationLogic(Bottom);

				SendMovePacket(ServerPosition.X, Bottom);
			}
		}
	}
	//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, FString::Printf(TEXT("%d, %d"), (int)ServerPosition.X, (int)ServerPosition.Y));
}

void APlayerCharacter::ReceiveNotifyDamaged(gen::mmo::NotifyDamaged NotifyDamagedPacket)
{
	GetSprite()->SetMaterial(0, DamagedMaterial);
	IsDamagedMaterialOn = true;
	DamagedMaterialTimer = DamagedMaterialTime;
}

void APlayerCharacter::ReceiveTakeAttack(gen::mmo::TakeAttack TakeAttackPacket)
{
	if (GetIsmine()) {
		auto Status = gen::mmo::HitStatus();
		if (IsParrying()) {
			Status.state = gen::mmo::EPlayerState::Parrying;
		}
		else if (IsJumping) {
			Status.state = gen::mmo::EPlayerState::Jump;
		}
		else if (IsAfterDelaying()) {
			Status.state = gen::mmo::EPlayerState::Attack;
		}
		else {
			Status.state = gen::mmo::EPlayerState::Idle;
		}
		UManager::Net()->Send(ServerType::MMO, &Status);
	}
}

void APlayerCharacter::DestroyNetObject()
{
	NetObject::DestroyNetObject();
	Destroy();
}

void APlayerCharacter::MoveInputHandler(const FInputActionValue& Value) {
	int Axis = Value.Get<float>();
	if (Axis != LastMoveInput) {
		if (LastMoveInput == 0 && LastInputTimer > 0.2f) {
			LastInputTimer = 0;

			LastSendPositionTime = GetWorld()->GetTimeSeconds() - 0.2f;
		}

		LastMoveInput = Axis;
	}
}

void APlayerCharacter::WeaponSwitchInputHandler(const FInputActionValue& Value)
{
	int Axis = (int)Value.Get<float>();

	int Index = (CurrentWeaponIndex + Axis) % MyWeapons.Num();
	if (Index < 0) {
		Index = MyWeapons.Num() - 1;
	}
	SwitchWeapon(Index);
}

void APlayerCharacter::JumpInputHandler() {
	auto MapData = UManager::Object()->GetCurrentMapData();

	if (MapData->GroundCast(LastSendPosX, LocalPositionY) != LocalPositionY || IsJumping || IsFalling) {
		return;
	}

	int Top = ServerPosition.Y + 3;

	LocalPositionY = Top;
	SendMovePacket(LastSendPosX + LastMoveInput, Top);
	RpcView::CallRPC(JumpAnimationLogic, RpcTarget::Other, Top);
	JumpAnimationLogic(Top);
}

void APlayerCharacter::AttackInputHandler()
{
	CurrentWeapon->LightAttackHandler(LastMoveInput);
}

void APlayerCharacter::ParryingInputHandler()
{
	CurrentWeapon->ParryingHandler(LastMoveInput);
}

void APlayerCharacter::Dash(int Direction)
{
	auto MapData = UManager::Object()->GetCurrentMapData();
	Vector2Int TargetPosition = MapData->RayCast(Vector2Int(LastSendPosX, ServerPosition.Y), Vector2Int(Direction, 0), 1);
	MoveLogic(FVector2D(LastSendPosX + Direction, ServerPosition.Y));
}

void APlayerCharacter::MoveLogic(FVector2D Position)
{
	FVector2D Origin = ServerPosition;
	Vector2Int PositionInt = Vector2Int(Position.X, Position.Y);
	auto MapData = UManager::Object()->GetCurrentMapData();
	if (!MapData->CheckInWorld(PositionInt)) {
		if (Position.X < 0) {
			Position.X = 0;
		}
		else if (Position.X >= MapData->GetXSize()) {
			Position.X = MapData->GetXSize() - 1;
		}
		if (Position.Y < 0) {
			Position.Y = 0;
		}
		else if (Position.Y >= MapData->GetYSize()) {
			Position.Y = MapData->GetYSize() - 1;
		}
	}

	TryUsePortal(PositionInt);
	SendMovePacket(Position.X, Position.Y);
}

void APlayerCharacter::MoveAnimationLogic(float Axis)
{
	if (Axis > 0)Axis = 1;
	else if (Axis < 0)Axis = -1;

	if (!IsJumping && !IsFalling && !IsActing()) {
		if (Axis == 0) {
			GetSprite()->SetFlipbook(IdleAnimation);
		}
		else {
			GetSprite()->SetFlipbook(WalkAnimation);
		}
	}

	if (Axis != LastMoveAnimationValue) {
		if (Axis != 0) {
			GetSprite()->SetWorldScale3D(FVector(SpriteOriginScale.X * Axis, SpriteOriginScale.Y, SpriteOriginScale.Z));

			CurruntPlayerDir = Axis;
		}
		LastMoveAnimationValue = Axis;
	}
}

void APlayerCharacter::JumpAnimationLogic(int Top)
{
	IsJumping = true;
	IsFalling = false;
	JumpAnimationStartZ = GetActorLocation().Z;
	JumpAnimationTimer = 0;
	GetSprite()->SetFlipbook(JumpAnimation);
	auto MapData = UManager::Object()->GetCurrentMapData();
	if (Top < MapData->GetYSize()) {
		JumpAnimationTop = Top * 100;
	}
	else {
		MapData->Log();
		JumpAnimationTop = (MapData->GetYSize() - 1) * 100;
	}
}

void APlayerCharacter::FallAnimationLogic(int Bottom)
{
	if (!IsJumping && !IsFalling) {
		IsJumping = false;
		IsFalling = true;
	}
	if (!IsJumping) {
		JumpAnimationTimer = 0;
		JumpAnimationTop = GetActorLocation().Z;
	}
	JumpAnimationBottom = Bottom * 100;
	GetSprite()->SetFlipbook(JumpAnimation);
}

void APlayerCharacter::FarryingAnimationLogic()
{
	GetSprite()->SetFlipbook(FarryingAnimation);
}

bool APlayerCharacter::IsActing()
{
	return IsAfterDelaying() || IsParrying();
}

void APlayerCharacter::SwitchWeapon(int WeaponIndex)
{
	auto Origin = CurrentWeapon;
	if (Origin != nullptr) {
		CurrentWeapon->OnSwitchedTo(MyWeapons[WeaponIndex]);
	}
	CurrentWeapon = MyWeapons[WeaponIndex];
	CurrentWeaponIndex = WeaponIndex;
	if (Origin != nullptr) {
		CurrentWeapon->OnSwitchedFrom(Origin);
	}
}

void APlayerCharacter::SetAfterDelay(float Delay)
{
	WeaponAfterDelay = Delay;
}

void APlayerCharacter::Parrying(float Time)
{
	if (Time > ParryingTimer) {
		ParryingTimer = Time;

		RpcView::CallRPC(FarryingAnimationLogic, RpcTarget::All);
	}
}

bool APlayerCharacter::IsAfterDelaying()
{
	return WeaponAfterDelay > 0;
}

bool APlayerCharacter::IsParrying()
{
	return ParryingTimer > 0;
}

void APlayerCharacter::RPCJump(int JumpPower)
{
	int Top = ServerPosition.Y + JumpPower;
	SendMovePacket(LastSendPosX + LastMoveInput, Top);
	RpcView::CallRPC(JumpAnimationLogic, RpcTarget::All, Top);
}

void APlayerCharacter::SendMovePacket(float X, float Y) {
	gen::mmo::Move MovePacket;
	MovePacket.position.x = X;
	MovePacket.position.y = Y;
	LastSendPosX = X;

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

TArray<AActor*> APlayerCharacter::ScanHitbox(FVector2D AddedPosition, FVector2D Scale, float Dir, bool IgnoreFlip)
{
	AddedPosition *= 2;
	AddedPosition += Scale;
	if (!IgnoreFlip) {
		AddedPosition.X *= CurruntPlayerDir;
		Dir *= CurruntPlayerDir;
	}

	auto Pos = GetActorLocation() + FVector(AddedPosition.X, 0, AddedPosition.Y);
	ETraceTypeQuery ObjectTypes = UEngineTypes::ConvertToTraceType(ECollisionChannel::ECC_WorldDynamic);
	TArray<AActor*> IgnoreActors;
	TArray<FHitResult> Results;

	UKismetSystemLibrary::BoxTraceMulti(
		GetWorld(),
		Pos,
		Pos,
		FVector(Scale.X, 0, Scale.Y),
		FRotator(-Dir, 0, 0),
		ObjectTypes,
		false,
		IgnoreActors,
		EDrawDebugTrace::ForDuration,
		Results,
		true
	);

	TArray <AActor*> Actors = TArray<AActor*>();
	for (auto Result : Results) {
		if (!Actors.Contains(Result.GetActor())) {
			Actors.Add(Result.GetActor());
		}
	}

	return Actors;
}

void APlayerCharacter::TryUsePortal(Vector2Int Position)
{
	auto MapData = UManager::Object()->GetCurrentMapData();
	if (MapData->GetTile(Position) == 3) {
		UManager::Object()->RequestEnterMap(MapData->GetPortalLinkName(Position));
	}
}
