// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Vector2Int.h"

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
	int GetTile(Vector2Int Position);
	int GetTile(int X, int Y);
	bool CheckIsWall(Vector2Int Position);
	bool CheckIsWall(int X, int Y);
	bool CheckInWorld(Vector2Int Position);
	bool CheckInWorld(int X, int Y);
	Vector2Int RayCast(Vector2Int Start, Vector2Int Direction);
	Vector2Int RayCast(Vector2Int Start, Vector2Int Direction, int Len);
	int GroundCast(Vector2Int Start);
	int GroundCast(int X, int Y);

	void Log(FColor Color = FColor::Magenta);

private:
	Vector2Int RayCast(Vector2Int Start, Vector2Int Direction, int Len, bool UseLen);
};
