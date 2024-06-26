// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameActor/Monster/Monster.h"
#include "GeminiRobot.generated.h"

/**
 * 
 */
UCLASS()
class WOS_API AGeminiRobot : public AMonster
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	virtual void AirBorne() override;
};
