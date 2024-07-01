// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "generated/mmo/Protocol.gen.hpp"

/**
 * 
 */
class WOS_API NetUtility
{
public:
	static gen::mmo::Vector2 MakeVector(FVector Vector);
	static FVector MakeVector(gen::mmo::Vector2 Vector);
};