// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Managers/ManagerBase.h"
#include "UISystem.generated.h"

/**
 * 
 */
UCLASS()
class WOS_API UUISystem : public UManagerBase
{
	GENERATED_BODY()
public:
	void ShowPopup(UWorld* World, FString Title, FString Content);
};
