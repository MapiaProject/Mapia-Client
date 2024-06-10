// Fill out your copyright notice in the Description page of Project Settings.


#include "GameActor/Player/PlayableController.h"

void APlayableController::BeginPlay() {
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
}