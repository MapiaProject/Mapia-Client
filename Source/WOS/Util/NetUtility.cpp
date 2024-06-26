// Fill out your copyright notice in the Description page of Project Settings.


#include "NetUtility.h"

gen::mmo::Vector2 NetUtility::MakeVector(FVector Vector)
{
	gen::mmo::Vector2 Vec2;
	Vec2.x = Vector.X;
	Vec2.y = Vector.Z;
	return Vec2;
}

FVector NetUtility::MakeVector(gen::mmo::Vector2 Vector)
{
	FVector FVec(Vector.x, 0, Vector.y);
	return FVec;
}
