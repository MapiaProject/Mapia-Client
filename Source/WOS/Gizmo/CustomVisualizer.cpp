// Fill out your copyright notice in the Description page of Project Settings.


#include "Gizmo/CustomVisualizer.h"
#include "MapLayoutViewer.h"

CustomVisualizer::CustomVisualizer()
{
}

CustomVisualizer::~CustomVisualizer()
{
}

void CustomVisualizer::DrawVisualization(const UActorComponent* Component, const FSceneView* View, FPrimitiveDrawInterface* PDI)
{
	const AMapLayoutViewer* SphereComponent = Cast<AMapLayoutViewer>(Component);
	if (SphereComponent)
	{
		const FVector SphereLocation = SphereComponent->GetActorLocation();
		const float SphereRadius = 100;
		const FColor SphereColor = FColor::Yellow;

		// Draw the sphere visualization
		DrawWireSphere(PDI, SphereLocation, SphereColor, SphereRadius, 16, SDPG_World);
	}
}
