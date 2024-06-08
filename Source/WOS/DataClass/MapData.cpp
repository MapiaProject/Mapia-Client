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

int MapData::GetTile(Vector2Int Position)
{
	return GetTile(Position.X, Position.Y);
}

int MapData::GetTile(int X, int Y)
{
	if (X >= GetXSize() || Y > GetYSize()) {
		return 0;
	}
	return TileData[Y][X];
}

bool MapData::CheckIsWall(Vector2Int Position)
{
	return CheckIsWall(Position.X, Position.Y);
}

bool MapData::CheckIsWall(int X, int Y)
{
	if (X > GetXSize() - 1 || Y > GetYSize()) return false;
	return GetTile(X, Y) == 1;
}

int MapData::GroundCast(Vector2Int Start)
{
	return GroundCast(Start.X, Start.Y);
}

int MapData::GroundCast(int X, int Y)
{
	auto CheckingPositionY = Y;
	while (CheckingPositionY >= 1) {
		if (!CheckIsWall(X, CheckingPositionY) && CheckIsWall(X, CheckingPositionY - 1)) {
			return CheckingPositionY;
		}

		CheckingPositionY -= 1;
	}

	return Y;
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
