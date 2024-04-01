// Fill out your copyright notice in the Description page of Project Settings.


#include "Gizmo/CustomVisualizer.h"
#include "MapLayoutViewer.h"
#include "Util/Ini.h"

CustomVisualizer::CustomVisualizer()
{
}

CustomVisualizer::~CustomVisualizer()
{
}

void CustomVisualizer::DrawVisualization(const UActorComponent* Component, const FSceneView* View, FPrimitiveDrawInterface* PDI)
{
	const UMapLayoutViewer* mapLayoutViewer = Cast<UMapLayoutViewer>(Component);
	//���õ� ���Ͱ� MapLayoutViewer ������Ʈ�� ���������� ���
	if (mapLayoutViewer)
	{
		showLayout = mapLayoutViewer->showLayout;
		FString path = TEXT("C:\\GitHub\\WOS-Client\\Source\\WOS\\Network\\generated\\") + mapLayoutViewer->mapName + TEXT(".ini");
		//������ ������� ����� �����
		if (!FPlatformFileManager::Get().GetPlatformFile().FileExists(*path)) {
			showLayout = false;
			xSize = 0;
			zSize = 0;
		}
		else {
			Ini ini = Ini(path);
			FString data = ini[TEXT("map")].Get<FString>("data");

			//�� �����Ͱ� �޶����� ��쿡�� ���� ����
			if (mapDataTxt != data) {
				mapDataTxt = data;
				
				//�� ������ ����
				FString size = ini[TEXT("info")].Get<FString>("size");
				FString xData, zData;
				size.Split(TEXT(","), &xData, &zData);
				xSize = FCString::Atoi(*xData);
				zSize = FCString::Atoi(*zData);

				//�� �迭 ����
				mapData.clear();
				for (int z = 0;z < zSize;z++) {
					mapData.push_back(vector<int>());
					for (int x = 0;x < xSize;x++) {
						TCHAR c = data[z * xSize + x];
						mapData[z].push_back(FCString::Atoi(&c));
					}
				}
			}
		}
	}

	//���õ� ���Ϳ� ������� ����� ���
	if (showLayout) {
		DrawWireBox(PDI, FBox(FVector::Zero(), FVector(boxSpacing.X * xSize, 0, boxSpacing.Z * zSize)), worldborderColor, 1);
		for (int z = 0;z < mapData.size();z++) {
			for (int x = 0;x < mapData[z].size();x++) {
				if (mapData[z][x] != 0) {
					int zPos = (mapData.size() - 1 - z) * boxSpacing.Z;
					FVector boxPos = FVector(x * boxSpacing.X, 0, zPos);
					DrawWireBox(PDI, FBox(boxPos, boxPos + boxSize), GetTileColor(mapData[z][x]), 1);
				}
			}
		}
	}
}

FColor CustomVisualizer::GetTileColor(int tileID) {
	switch (tileID) {
	case 1:
		return groundColor;
	case 2:
		return monsterSpawnPosColor;
	case 3:
		return portalColor;
	default:
		return FColor::Magenta;
	}
}