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

	virtual void BeginPlay() override;
};
