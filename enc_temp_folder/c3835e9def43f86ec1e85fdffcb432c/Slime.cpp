// Fill out your copyright notice in the Description page of Project Settings.


#include "GameActor/Monster/Slime.h"
#include "PaperFlipbookComponent.h"

void ASlime::BeginPlay()
{
	SetName(TEXT("Slime"));
}

void ASlime::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

void ASlime::ReceiveNotifyMove(gen::mmo::NotifyMove MovePacket)
{

}

void ASlime::AirBorne()
{
}
