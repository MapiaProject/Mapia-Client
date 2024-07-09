// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Managers/ManagerBase.h"
#include "SQLiteDatabase.h"
#include "DataLoadManager.generated.h"

/**
 * 
 */
UCLASS()
class WOS_API UDataLoadManager : public UManagerBase
{
	GENERATED_BODY()
	
public:
	int LoadMonsterHP(FString Name);
	void LoadMonsterDropItem(FString Name);
	FString LoadItem(FString Name);

private:
	FSQLiteDatabase* Database;
	FSQLitePreparedStatement* PState;

};