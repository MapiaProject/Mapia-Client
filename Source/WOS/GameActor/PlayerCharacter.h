// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NetObject.h"
#include "Packet.h"
#include "PaperCharacter.h"
#include "PaperFlipbook.h"
#include "Network/generated/mmo/Protocol.gen.hpp"
#include "PlayerCharacter.generated.h"

UCLASS()
class WOS_API APlayerCharacter : public APaperCharacter, public NetObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Category = Animation)
		TObjectPtr<UPaperFlipbook> IdleAnimation;
	UPROPERTY(EditAnywhere, Category = Animation)
		TObjectPtr<UPaperFlipbook> WalkAnimation;
	UPROPERTY(EditAnywhere, Category = Animation)
		TObjectPtr<UPaperFlipbook> DashAnimation;
	UPROPERTY(EditAnywhere, Category = Animation)
		TObjectPtr<UPaperFlipbook> JumpAnimation;
	UPROPERTY(EditAnywhere, Category = Animation)
		TObjectPtr<UPaperFlipbook> Attack1Animation;
	UPROPERTY(EditAnywhere, Category = Animation)
		TObjectPtr<UPaperFlipbook> Attack2Animation;
	UPROPERTY(EditAnywhere, Category = Animation)
		TObjectPtr<UPaperFlipbook> DieAnimation;
	

	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
  
	virtual void RecievePacket(const Packet* ReadingPacket);
  
	virtual void MovePacketHandler(gen::mmo::Move MovePacket);

	void SetName(FStringView SettedName);
private:
	FString Name;
};
