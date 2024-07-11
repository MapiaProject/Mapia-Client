// Fill out your copyright notice in the Description page of Project Settings.


#include "GameActor/Projectile.h"

void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MoveTimer += DeltaTime;
	auto RetPos = Lerp(StartPos, DestinationPos, MoveTimer / 0.2f) * 100;
	SetActorLocation(FVector(RetPos.X, 0, RetPos.Y));
}

void AProjectile::ReceivePacket(const Packet* ReadingPacket)
{
	switch (ReadingPacket->GetId()) {
	case gen::mmo::PacketId::NOTIFY_MOVE:
		ReceiveNotifyMove(*static_cast<const gen::mmo::NotifyMove*>(ReadingPacket));
		break;
	}
}

bool AProjectile::TakeDamage(int Damage)
{
	return false;
}

void AProjectile::DestroyNetObject()
{
	Destroy();
}

void AProjectile::ReceiveNotifyMove(gen::mmo::NotifyMove MovePacket)
{
	FVector curPos = GetActorLocation();
	StartPos = FVector2D(curPos.X, curPos.Z);
	DestinationPos = FVector2D(MovePacket.position.x, MovePacket.position.y);
	MoveTimer = 0;
	
	FVector2D forward = DestinationPos - StartPos;
	FRotator Rot = GetActorRotation();
	SetActorRotation(FRotator(FMath::Acos(forward.Dot(FVector2D(0, 1))), Rot.Yaw, Rot.Roll));
}

float AProjectile::Lerp(float a, float b, float t)
{
	return a + (b - a) * t;
}

FVector2D AProjectile::Lerp(FVector2D a, FVector2D b, float t)
{
	return FVector2D(Lerp(a.X, b.X, t), Lerp(a.Y, b.Y, t));
}
