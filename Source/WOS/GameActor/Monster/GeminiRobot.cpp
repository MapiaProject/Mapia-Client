// Fill out your copyright notice in the Description page of Project Settings.


#include "GameActor/Monster/GeminiRobot.h"
#include "PaperFlipbookComponent.h"

void AGeminiRobot::BeginPlay()
{
	Super::BeginPlay();

}

void AGeminiRobot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SetName(TEXT("GeminiRobot"));

}

void AGeminiRobot::AirBorne()
{
	Super::AirBorne();
}