// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LocalPlayerController.generated.h"

/**
 *
 */
UCLASS()
class WOS_API ALocalPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void SetupInputComponent()override;

	void MoveHandler(float Axis);
	void JumpHandler();
	void AttackHandler();

private:
	float LastMoveInput;
};
