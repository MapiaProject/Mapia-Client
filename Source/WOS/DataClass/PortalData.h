// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Vector2Int.h"

/**
 * 
 */
class WOS_API PortalData
{
public:
	PortalData();
	PortalData(FString LinkName, Vector2Int Position);
	~PortalData();

	FString LinkName;
	Vector2Int Position;
};
