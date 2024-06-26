// Fill out your copyright notice in the Description page of Project Settings.


#include "GameActor/Monster/GeminiRobot.h"
#include "PaperFlipbookComponent.h"

void AGeminiRobot::BeginPlay()
{
	Super::BeginPlay();

	SetName(TEXT("GeminiRobot"));
}

void AGeminiRobot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGeminiRobot::AirBorne()
{
	Super::AirBorne();
}