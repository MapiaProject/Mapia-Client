// Fill out your copyright notice in the Description page of Project Settings.


#include "DataClass/Vector2Int.h"

Vector2Int::Vector2Int() : Vector2Int(0, 0)
{

}

Vector2Int::Vector2Int(int X, int Y)
{
	this->X = X;
	this->Y = Y;
}

Vector2Int::~Vector2Int()
{
}

Vector2Int Vector2Int::operator+(Vector2Int Other)
{
	return Vector2Int(X + Other.X, Y + Other.Y);
}

Vector2Int Vector2Int::operator-(Vector2Int Other)
{
	return Vector2Int(X - Other.X, Y - Other.Y);
}

Vector2Int Vector2Int::operator*(int Scalar)
{
	return Vector2Int(X * Scalar, Y * Scalar);
}

bool Vector2Int::operator==(Vector2Int Other)
{
	return X == Other.X && Y == Other.Y;
}

bool Vector2Int::operator!=(Vector2Int Other)
{
	return !(*this == Other);
}

FVector2D Vector2Int::GetFVector2D()
{
	return FVector2D(X, Y);
}

FVector Vector2Int::GetFVector()
{
	return FVector(X, Y, 0);
}

Vector2Int Vector2Int::Max(Vector2Int A, Vector2Int B)
{
	return Vector2Int(A.X > B.X ? A.X : B.X, A.Y > B.Y ? A.Y : B.Y);
}

Vector2Int Vector2Int::Min(Vector2Int A, Vector2Int B)
{
	return Vector2Int(A.X < B.X ? A.X : B.X, A.Y < B.Y ? A.Y : B.Y);
}

Vector2Int Vector2Int::Clamp(Vector2Int Value, Vector2Int MinValue, Vector2Int MaxValue)
{
	return Min(Max(Value, MinValue), MaxValue);
}

FString Vector2Int::ToString()
{
	return FString::Printf(TEXT("(%d, %d)"), X, Y);
}
