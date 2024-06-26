// Fill out your copyright notice in the Description page of Project Settings.


#include "GameActor/Monster/Monster.h"
#include "PaperFlipbookComponent.h"
#include "Components/WidgetComponent.h"
#include "UI/MonsterInfoUI.h"

AMonster::AMonster() {
	MonsterInfoUI = CreateDefaultSubobject<UWidgetComponent>(TEXT("MonsterInfoUI"));
	MonsterInfoUI->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

void AMonster::BeginPlay() {
	Super::BeginPlay();

	GetSprite()->SetMaterial(0, DamagedMaterial);
	GetSprite()->SetFlipbook(IdleAnimation);

	SetName(TEXT("MonsterName"));
}

void AMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (DamageEffectOn) {
		CurDamageEffectTime += DeltaTime;
		if (CurDamageEffectTime >= MaxDamageEffectTime) {
			GetSprite()->SetMaterial(0, DefaultMaterial);
			DamageEffectOn = false;
			CurDamageEffectTime = 0;
		}
	}

	MoveTimer += DeltaTime;
	auto retPos = Lerp(StartPos, DestinationPos, MoveTimer / 0.2f);
	
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
	Cast<UMonsterInfoUI>(MonsterInfoUI->GetUserWidgetObject())->SetName(Name);
}

void AMonster::SetHP(float MaxHP, float CurHP)
{
	Cast<UMonsterInfoUI>(MonsterInfoUI)->SetHP(0, 0);
}

void AMonster::Attack()
{
	GetSprite()->SetFlipbook(AttackAnimation);
}

void AMonster::AirBorne()
{
	GetSprite()->SetFlipbook(AirborneAnimation);
}

float AMonster::Lerp(float a, float b, float t)
{
	return a + (b - a) * t;
}

FVector2D AMonster::Lerp(FVector2D a, FVector2D b, float t)
{
	return FVector2D(Lerp(a.X, b.X, t), Lerp(a.Y, b.Y, t));
}

