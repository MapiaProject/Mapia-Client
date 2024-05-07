// Fill out your copyright notice in the Description page of Project Settings.


#include "GameActor/PlayableController.h"

void APlayableController::BeginPlay() {
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
}