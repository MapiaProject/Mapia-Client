// Fill out your copyright notice in the Description page of Project Settings.


#include "DataClass/MapData.h"

MapData::MapData() : MapData("", TArray<TArray<int>>(), TArray<FString>())
{

}

MapData::MapData(FString MapName, TArray<TArray<int>> TileData, TArray<FString> PortalLinks, FString SpawnMonsterName)
{
	this->Name = MapName;
	this->TileData = TileData;
	this->SpawnMonsterName = SpawnMonsterName;



	PortalDatas = TArray<PortalData>();
	int PortalCount = 0;
	for (int y = GetYSize() - 1;y > 0;y--) {
		for (int x = 0;x < GetXSize();x++) {
			if (TileData[y][x] == 3) {
				PortalDatas.Add(PortalData(PortalLinks[PortalCount], Vector2Int(x, y)));
				PortalCount++;
			}
		}
	}
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
	if (!CheckInWorld(X, Y)) {
		return 1;
	}
	return TileData[Y][X];
}

FString MapData::GetSpawnMonsterName()
{
	return SpawnMonsterName;
}

int MapData::GetPortalCount()
{
	return PortalDatas.Num();
}

FString MapData::GetPortalLinkName(Vector2Int Position)
{
	return GetPortalLinkName(Position.X, Position.Y);
}

FString MapData::GetPortalLinkName(int X, int Y)
{
	if (CheckInWorld(X, Y) && GetTile(X, Y) == 3) {
		for (int i = 0;i < PortalDatas.Num();i++) {
			if (PortalDatas[i].Position.X == X && PortalDatas[i].Position.Y == Y) {
				return PortalDatas[i].LinkName;
			}
		}
	}
	return TEXT("");
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

bool MapData::CheckInWorld(Vector2Int Position)
{
	return CheckInWorld(Position.X, Position.Y);
}

bool MapData::CheckInWorld(int X, int Y)
{
	return X >= 0 && Y >= 0 && X < GetXSize() && Y < GetYSize();
}

Vector2Int MapData::RayCast(Vector2Int Start, Vector2Int Direction)
{
	return RayCast(Start, Direction, 0, false);
}

Vector2Int MapData::RayCast(Vector2Int Start, Vector2Int Direction, int Len)
{
	return RayCast(Start, Direction, Len, true);
}

FVector2D MapData::RayCast(FVector2D Start, Vector2Int Direction)
{
	if (Direction == Vector2Int(0, 0)) {
		return Start;
	}

	auto StartInt = Vector2Int(Start);
	FVector2D RayResult = RayCast(StartInt, Direction).GetFVector2D() + StartInt.GetFVector2D() - Start;
	return RayResult;
}

FVector2D MapData::RayCast(FVector2D Start, Vector2Int Direction, float Len)
{
	FVector2D RayResult = RayCast(Start, Direction);

	if ((RayResult - Start).Length() > Len) {
		RayResult = Start + (RayResult - Start).GetSafeNormal() * Len;
	}

	return RayResult;
}

int MapData::GroundCast(Vector2Int Start)
{
	return GroundCast(Start.X, Start.Y);
}

int MapData::GroundCast(int X, int Y)
{
	return RayCast(Vector2Int(X, Y), Vector2Int(0, -1)).Y;
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

Vector2Int MapData::RayCast(Vector2Int Start, Vector2Int Direction, int Len, bool UseLen)
{
	if (Direction == Vector2Int(0, 0)) {
		return Start;
	}

	Vector2Int Current = Start;
	for (int a = 0;!UseLen || a < Len;a++) {
		if (CheckIsWall(Current + Direction) || !CheckInWorld(Current + Direction)) {
			break;
		}
		Current = Current + Direction;
	}

	return Current;
}
