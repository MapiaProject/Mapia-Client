// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NetObject.h"
#include "Packet.h"
#include "PaperCharacter.h"
#include "PaperFlipbook.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Managers/NetObjectManager.h"
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

	UPROPERTY(EditAnywhere, Category = Input)
		TObjectPtr<UInputMappingContext> InputMappingContext;
	UPROPERTY(EditAnywhere, Category = Input)
		TObjectPtr<UInputAction> MoveAction;
	UPROPERTY(EditAnywhere, Category = Input)
		TObjectPtr<UInputAction> JumpAction;
	UPROPERTY(EditAnywhere, Category = Input)
		TObjectPtr<UInputAction> AttackAction;
	UPROPERTY(EditAnywhere, Category = Move)
		float MoveSpeed;

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

	virtual void HandleMove(gen::mmo::NotifyMove MovePacket);
	virtual void DestroyNetObject() override;

	void SetName(FStringView SettedName);
	void SetIsmine();
	bool GetIsmine();
private:
	FString Name;

	void MoveHandler(const FInputActionValue& Value);
	void JumpHandler();
	void AttackHandler();
	void SendMovePacket(float X, float Y);

	static constexpr float sendPositionInterval = 0.2f;

	float LastMoveInput;
	float LastSendPositionTime;
	FVector SpriteOriginScale;
	bool bIsmine;
};
