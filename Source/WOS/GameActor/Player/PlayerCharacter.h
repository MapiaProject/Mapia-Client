// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../NetObject.h"
#include "Packet.h"
#include "PaperCharacter.h"
#include "PaperFlipbook.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Managers/NetObjectManager.h"
#include "rpc.h"
#include "DataClass/Vector2Int.h"
#include "Weapon.h"
#include "Network/generated/mmo/Protocol.gen.hpp"
#include "PlayerCharacter.generated.h"

UCLASS()
class WOS_API APlayerCharacter : public APaperCharacter, public NetObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Category = Weapon)
		TArray<TSubclassOf<UWeapon>> StartingWeapon;

	UPROPERTY(EditAnywhere, Category = Move)
		float MoveSpeed;

	UPROPERTY(EditAnywhere, Category = Input)
		TObjectPtr<UInputMappingContext> InputMappingContext;
	UPROPERTY(EditAnywhere, Category = Input)
		TObjectPtr<UInputAction> MoveAction;
	UPROPERTY(EditAnywhere, Category = Input)
		TObjectPtr<UInputAction> WeaponSwitchAction;
	UPROPERTY(EditAnywhere, Category = Input)
		TObjectPtr<UInputAction> JumpAction;
	UPROPERTY(EditAnywhere, Category = Input)
		TObjectPtr<UInputAction> AttackAction;
	UPROPERTY(EditAnywhere, Category = Input)
		TObjectPtr<UInputAction> ParryingAction;

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
	UPROPERTY(EditAnywhere, Category = Animation)
		TObjectPtr<UMaterialInterface> DefaultMaterial;
	UPROPERTY(EditAnywhere, Category = Animation)
		TObjectPtr<UMaterialInterface> DamagedMaterial;
	UPROPERTY(EditAnywhere, Category = Animation)
		float DamagedMaterialTime;



	// Sets default values for this character's properties
	APlayerCharacter();
	friend UWeapon;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void ReceivePacket(const Packet* ReadingPacket) override;

	virtual void ReceiveNotifyMove(gen::mmo::NotifyMove MovePacket);
	virtual void ReceiveNotifyDamaged(gen::mmo::NotifyDamaged NotifyDamagedPacket);
	virtual void ReceiveTakeAttack(gen::mmo::TakeAttack TakeAttackPacket);
	virtual void DestroyNetObject() override;

	void SetName(FStringView SettedName);
	void HandleSpawn(Vector2Int Position);
	void SetIsmine();
	bool GetIsmine();
	bool IsAfterDelaying();
	bool IsParrying();

	void RPCJump(int JumpPower);

private:
	void MoveInputHandler(const FInputActionValue& Value);
	void WeaponSwitchInputHandler(const FInputActionValue& Value);
	void JumpInputHandler();
	void AttackInputHandler();
	void ParryingInputHandler();

	void Dash(int Direction);
	void MoveLogic(Vector2Int Position);
	void MoveAnimationLogic(float Axis);
	RPC_FUNCTION(JumpAnimationLogic)
		void JumpAnimationLogic(int Top);
	RPC_FUNCTION(FallAnimationLogic)
		void FallAnimationLogic(int Bottom);
	float JumpAnimationStartZ;
	float JumpAnimationTop;
	float JumpAnimationBottom;
	float JumpAnimationTimer;
	bool IsJumping;
	bool IsFalling;

	void SwitchWeapon(int WeaponIndex);
	void SetAfterDelay(float Delay);
	void SendMovePacket(float X, float Y);
	float Lerp(float a, float b, float t);
	FVector2D Lerp(FVector2D a, FVector2D b, float t);

	TArray<AActor*> ScanHitbox(FVector2D AddedPosition, FVector2D Scale, float Dir = 0, bool IgnoreFlip = false);
	void TryUsePortal(Vector2Int Position);

	static constexpr float sendPositionInterval = 0.2f;
	FString Name;

	//위치 계산, 애니메이션 구현용 변수
	float LastMoveInput;
	float LastSendPositionTime;
	FVector SpriteOriginScale;
	bool bNetObjectIsmine;
	Vector2Int LastPosition;
	float LastInputTimer;
	float LastMoveAnimationValue;
	int LastSendPosX;
	float CurruntPlayerDir;
	Vector2Int ServerPosition;
	int LocalPositionY;
	float ServerTimer;

	TArray<UWeapon*> MyWeapons;
	TObjectPtr<UWeapon> CurrentWeapon = nullptr;
	int CurrentWeaponIndex;
	float WeaponAfterDelay;

	float DamagedMaterialTimer;
	bool IsDamagedMaterialOn;
	float ParryingTimer;
};
