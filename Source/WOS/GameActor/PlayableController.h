// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayableController.generated.h"

/**
 *
 */
UCLASS()
class WOS_API APlayableController : public APlayerController
{

	GENERATED_BODY()

public:
	APlayableController();

	virtual void SetupInputComponent()override;
	virtual void Tick(float DeltaTime)override;

	void MoveHandler(float Axis);
	void JumpHandler();
	void AttackHandler();

private:
 	static constexpr float sendPositionInterval = 0.2f;

	float LastMoveInput;
	float LastSendPositionTime;
};
