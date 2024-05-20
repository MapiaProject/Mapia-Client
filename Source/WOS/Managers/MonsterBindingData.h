// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "generated/mmo/Struct.gen.hpp"
#include "MonsterBindingData.generated.h"

/**
 *
 */
UCLASS()
class WOS_API UMonsterBindingData : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Category = BindingData)
		TArray<TSubclassOf<AActor>> MonsterActors;
};
