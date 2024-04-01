// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ComponentVisualizer.h"
#include <vector>
using namespace std;

/**
 *
 */
class WOS_API CustomVisualizer : public FComponentVisualizer
{
public:
	CustomVisualizer();
	~CustomVisualizer();
	virtual void DrawVisualization(const UActorComponent* Component, const FSceneView* View, FPrimitiveDrawInterface* PDI) override;
private:
	const FVector boxSpacing = FVector(100, 100, 100);
	const FVector boxSize = boxSpacing - FVector::One() * 0.1f;
	const FColor groundColor = FColor::Black;
	const FColor monsterSpawnPosColor = FColor::Green;
	const FColor portalColor = FColor::Cyan;
	const FColor worldborderColor = FColor::Red;

	FString mapDataTxt = "";
	bool showLayout = true;
	vector<vector<int>> mapData;
	int xSize;
	int zSize;

	FColor GetTileColor(int tileID);
};
