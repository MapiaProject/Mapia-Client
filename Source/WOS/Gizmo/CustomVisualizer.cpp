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
	UE_LOG(LogTemp, Log, TEXT("Visual"));
	const UMapLayoutViewer* SphereComponent = Cast<UMapLayoutViewer>(Component);
	if (SphereComponent)
	{
		//const FVector SphereLocation = SphereComponent->GetActorLocation();
		const FVector SphereLocation = FVector::Zero();
		const float SphereRadius = 100;
		const FColor SphereColor = FColor::Yellow;

		DrawWireSphere(PDI, SphereLocation, SphereColor, SphereRadius, 16, SDPG_World);
	}
}

void CustomVisualizer::DrawVisualizationHUD(const UActorComponent* Component, const FViewport* Viewport, const FSceneView* View, FCanvas* Canvas) {
	UE_LOG(LogTemp, Log, TEXT("HUD"));
}