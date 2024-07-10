// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class WOS_API Vector2Int
{
public:
	Vector2Int();
	Vector2Int(int X, int Y);
	Vector2Int(FVector2D Pos);
	~Vector2Int();

	Vector2Int operator +(Vector2Int Other);
	Vector2Int operator -(Vector2Int Other);
	Vector2Int operator *(int Scalar);
	Vector2Int operator +=(Vector2Int Other);
	Vector2Int operator -=(Vector2Int Other);
	bool operator ==(Vector2Int Other);
	bool operator !=(Vector2Int Other);
	
	FVector2D GetFVector2D();
	FVector GetFVector();
	static Vector2Int Max(Vector2Int A, Vector2Int B);
	static Vector2Int Min(Vector2Int A, Vector2Int B);
	static Vector2Int Clamp(Vector2Int Value,Vector2Int MinValue,Vector2Int MaxValue);
	FString ToString();

	int X, Y;
};
