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
	//선택된 액터가 MapLayoutViewer 컴포넌트를 가지고있을 경우
	if (mapLayoutViewer)
	{
		showLayout = mapLayoutViewer->showLayout;
		FString path = TEXT("C:\\GitHub\\WOS-Client\\Source\\WOS\\Network\\generated\\") + mapLayoutViewer->mapName + TEXT(".ini");
		//파일이 없을경우 기즈모 숨기기
		if (!FPlatformFileManager::Get().GetPlatformFile().FileExists(*path)) {
			showLayout = false;
			xSize = 0;
			zSize = 0;
		}
		else {
			Ini ini = Ini(path);
			FString data = ini[TEXT("map")].Get<FString>("data");

			//맵 데이터가 달라졌을 경우에만 정보 추출
			if (mapDataTxt != data) {
				mapDataTxt = data;
				
				//맵 사이즈 추출
				FString size = ini[TEXT("info")].Get<FString>("size");
				FString xData, zData;
				size.Split(TEXT(","), &xData, &zData);
				xSize = FCString::Atoi(*xData);
				zSize = FCString::Atoi(*zData);

				//맵 배열 생성
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

	//선택된 액터와 관계없이 기즈모 출력
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