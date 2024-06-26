// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MapLayoutViewer.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class WOS_API UMapLayoutViewer : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	FString mapName;
	UPROPERTY(EditAnywhere)
	bool showLayout = true;

	UMapLayoutViewer();
};
