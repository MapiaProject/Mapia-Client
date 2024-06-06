// Fill out your copyright notice in the Description page of Project Settings.


#include "DataClass/MapData.h"

MapData::MapData() : MapData("", TArray<TArray<int>>())
{

}

MapData::MapData(FString MapName, TArray<TArray<int>> TileData)
{
	this->Name = MapName;
	this->TileData = TileData;
}

MapData::~MapData()
{
}

FString MapData::GetName()
{
	return Name;
}

int MapData::GetXSize()
{
	if (GetYSize() == 0)return 0;
	return TileData[0].Num();
}

int MapData::GetYSize()
{
	return TileData.Num();
}

int MapData::GetTile(int X, int Y)
{
	if (X >= GetXSize() || Y > GetYSize()) {
		return 0;
	}
	return TileData[Y][X];
}

bool MapData::CheckIsWall(int X, int Y)
{
	return GetTile(X, Y) == 1;
}

void MapData::Log(FColor Color)
{
	FString s = TEXT("");
	for (int i = 0;i < GetYSize();i++) {
		FString temp = TEXT("");
		for (int j = 0;j < GetXSize();j++) {
			temp += FString::Printf(TEXT("%d"), GetTile(j, i));
		}
		s = temp + TEXT("\n") + s;
	}
	GEngine->AddOnScreenDebugMessage(-1, 5, Color, FString::Printf(TEXT("Tile : \n%s"), *s));
	GEngine->AddOnScreenDebugMessage(-1, 5, Color, FString::Printf(TEXT("Size : %d x %d"), GetXSize(), GetYSize()));
	GEngine->AddOnScreenDebugMessage(-1, 5, Color, TEXT("MapDataLog"));
	GEngine->AddOnScreenDebugMessage(-1, 5, Color, TEXT("==============="));
}
