// Fill out your copyright notice in the Description page of Project Settings.


#include "GameActor/Monster/Monster.h"
#include "PaperFlipbookComponent.h"
#include "Components/WidgetComponent.h"
#include "UI/MonsterInfoUI.h"

AMonster::AMonster() {
	MonsterInfoUI = CreateDefaultSubobject<UWidgetComponent>(TEXT("MonsterInfoUI"));
	MonsterInfoUI->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	AirBorneAnimationTimer = 0;
	StartPos = FVector2D(9, 2);
	DestinationPos = FVector2D(9, 2);
}

void AMonster::BeginPlay() {
	Super::BeginPlay();

	GetSprite()->SetMaterial(0, DamagedMaterial);
	GetSprite()->SetFlipbook(IdleAnimation);
}

void AMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	DeltaTimeCopy = DeltaTime;
	if (DamageEffectOn) {
		CurDamageEffectTime += DeltaTime;
		if (CurDamageEffectTime >= MaxDamageEffectTime) {
			GetSprite()->SetMaterial(0, DefaultMaterial);
			DamageEffectOn = false;
			CurDamageEffectTime = 0;
		}
	}

	MoveTimer += DeltaTime;
	auto RetPos = Lerp(StartPos, DestinationPos, MoveTimer) * 100;
	SetActorLocation(FVector(RetPos.X, 0, RetPos.Y));


	if (isAirBorne) {
		AirBorneAnimationTimer += DeltaTime;
		StartPos = FVector2D(DestinationPos.X, DestinationPos.Y);
		DestinationPos = FVector2D(DestinationPos.X, DestinationPos.Y + AirBornePower);
		AirBornePower -= Difference;
		MoveTimer = 1 - DeltaTime;
		if (AirBorneAnimationTimer >= AirBorneAnimationTime) {
			AirBorneAnimationTimer = 0;
			isAirBorne = false;
			StartPos = FVector2D(GetActorLocation().X / 100, GetActorLocation().Z / 100);
			DestinationPos = FVector2D(StartPos.X, StartPos.Y);
		}
	}
	else if (isAttack) {
		AttackAnimationTimer += DeltaTime;
		if (AttackAnimationTimer >= AttackAnimationTime) {
			AttackAnimationTimer = 0;
			isAttack = false;
		}
	}
	else {
		Move();
	}
}

void AMonster::ReceivePacket(const Packet* ReadingPacket)
{
	switch (ReadingPacket->GetId()) {
	case gen::mmo::PacketId::NOTIFY_MOVE:
		ReceiveNotifyMove(*static_cast<const gen::mmo::NotifyMove*>(ReadingPacket));
		break;
	}
}

void AMonster::ReceiveNotifyMove(gen::mmo::NotifyMove MovePacket)
{
	FVector curPos = GetActorLocation();
	StartPos = FVector2D(curPos.X, curPos.Z);
	DestinationPos = FVector2D(MovePacket.position.x, MovePacket.position.y);
	MoveTimer = 0;

	float RetSub = StartPos.X - DestinationPos.X;
	Dir = RetSub / abs(RetSub);
}

bool AMonster::TakeDamage(int Damage)
{
	bool IsDamaged = NetObject::TakeDamage(Damage);
	if (IsDamaged) {
		GetSprite()->SetMaterial(0, DamagedMaterial);
		DamageEffectOn = true;
	}
	return IsDamaged;
}

void AMonster::DestroyNetObject()
{
	Destroy();
}

void AMonster::SetName(FString Name)
{
	if (auto WidgetObject = MonsterInfoUI->GetUserWidgetObject()) Cast<UMonsterInfoUI>(WidgetObject)->SetName(Name);
}

void AMonster::SetHP(float MaxHP, float CurHP)
{
	if (auto WidgetObject = MonsterInfoUI->GetUserWidgetObject()) Cast<UMonsterInfoUI>(WidgetObject)->SetHP(MaxHP, CurHP);
}

void AMonster::Attack()
{
	GetSprite()->SetFlipbook(AttackAnimation);
}

void AMonster::Move() {
	if (Dir) {
		FVector curScale = GetSprite()->GetRelativeScale3D();
		curScale.X = Dir * abs(curScale.X);
		GetSprite()->SetRelativeScale3D(curScale);
		GetSprite()->SetFlipbook(WalkAnimation);
	}
	else {
		GetSprite()->SetFlipbook(IdleAnimation);
	}
}

void AMonster::AirBorne()
{
	GetSprite()->SetFlipbook(AirborneAnimation);
	isAirBorne = true;

	RepeatCnt = AirBorneAnimationTime / DeltaTimeCopy;
	IsRepeatCntOdd = RepeatCnt & 1;
	RepeatCnt /= 2;

	Difference = 380.0f / ((RepeatCnt + 1) * RepeatCnt) / 60;

	AirBornePower = Difference * RepeatCnt;
}

float AMonster::Lerp(float a, float b, float t)
{
	return a + (b - a) * t;
}

FVector2D AMonster::Lerp(FVector2D a, FVector2D b, float t)
{
	return FVector2D(Lerp(a.X, b.X, t), Lerp(a.Y, b.Y, t));
}