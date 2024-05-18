// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/NetObjectManager.h"
#include "GameFramework/Character.h"
#include "GameActor/LocalPlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include <UObject/ConstructorHelpers.h>

#define GetBPClass(ValueName,BPName,ClassType) static ConstructorHelpers::FClassFinder<ClassType> BP(TEXT("/Script/Engine.Blueprint'/Game/Blueprints/GameActor/"#BPName"."#BPName"_C'"));\
if (BP.Succeeded())\
{\
	ValueName = BP.Class;\
}

UNetObjectManager::UNetObjectManager()
{
	GetBPClass(LocalPlayerClass,BP_LocalPlayerCharacter,ACharacter)
	GetBPClass(PlayerClass,BP_PlayerCharacter,ACharacter)
}

void UNetObjectManager::HandleSpawnPlayer(uint64 ObjectId, FVector Position, FString Name, bool bIsMine) {
	auto* World = GetWorld();
	auto Rotation = FRotator(0, 0, 0);
	APlayerCharacter* Player = nullptr;

	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Emerald, FString::Printf(TEXT("(%f, %f)"), Position.X, Position.Z));

	Position *= 100;


	if (bIsMine) {

		auto* Actor = World->SpawnActor(LocalPlayerClass, &Position, &Rotation);

		Player = Cast<ALocalPlayerCharacter>(Actor);
		Player->ObjectId = ObjectId;

		auto Controller = UGameplayStatics::GetPlayerController(World, 0);
		Player->Controller = Controller;
		Controller->Possess(Player);
	}
	else {
		auto* Actor = World->SpawnActor(PlayerClass, &Position, &Rotation);
		Player = Cast<APlayerCharacter>(Actor);
		Player->ObjectId = ObjectId;
	}
	Player->SetName(Name);
	NetObjects.Add(ObjectId, Player);
}

void UNetObjectManager::HandleLeaveMap(uint64 ObjectId)
{
	NetObjects[ObjectId]->HandleLeaveMap();
}

void UNetObjectManager::HandleSpawnMonster(gen::mmo::ObjectInfo MonsterInfo, gen::mmo::EMonsterType MonsterType)
{
	
}

void UNetObjectManager::HandleNetObjectPacket(uint64 ObjectId, const Packet* RecievedPacket) {
	if (NetObjects.Contains(ObjectId)) {
		NetObjects[ObjectId]->RecievePacket(RecievedPacket);
	}
}