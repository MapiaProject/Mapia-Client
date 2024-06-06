// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class WOS_API MapData
{
private:
	FString Name;
	TArray<TArray<int>> TileData;

public:
	MapData();
	MapData(FString MapName, TArray<TArray<int>> TileData);
	~MapData();

	FString GetName();
	int GetXSize();
	int GetYSize();
	int GetTile(int X, int Y);
	bool CheckIsWall(int X, int Y);

	void Log(FColor Color = FColor::Magenta);
};
