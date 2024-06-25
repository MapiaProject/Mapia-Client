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
}

void AMonster::DestroyNetObject()
{
	Destroy();
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

void AMonster::SetName(FString Name)
{
	if (MonsterInfoUI->GetUserWidgetObject()) {
		UE_LOG(LogTemp, Warning, TEXT("NOT NULL"));
	}
	else 
		UE_LOG(LogTemp, Warning, TEXT("NULL"));

	UE_LOG(LogTemp, Warning, TEXT("NULL"));
	//Cast<UMonsterInfoUI>(MonsterInfoUI)->SetName(Name);
}

void AMonster::SetHP()
{
	//Cast<UMonsterInfoUI>(MonsterInfoUI)->SetHP(0, 0);
}

void AMonster::Attack()
{
}

void AMonster::Move()
{
}

void AMonster::AirBorne()
{
}

float AMonster::Lerp(float a, float b, float t)
{
	return a + (b - a) * t;
}

FVector2D AMonster::Lerp(FVector2D a, FVector2D b, float t)
{
	return FVector2D(Lerp(a.X, b.X, t), Lerp(a.Y, b.Y, t));
}

