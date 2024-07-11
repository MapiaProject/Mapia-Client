// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/DataLoadManager.h"

int UDataLoadManager::LoadMonsterHP(FString Name)
{
	int HP = 0;

	Database = new FSQLiteDatabase();

	const FString Path = FPaths::ProjectContentDir() + "Database/datasheet.db";
	if (Database->Open(*Path, ESQLiteDatabaseOpenMode::ReadWrite)) {

		PState = new FSQLitePreparedStatement();

		const TCHAR* LoadQuery = TEXT("select hp from monster where ptype = $ptype;");
		if (PState->Create(*Database, LoadQuery, ESQLitePreparedStatementFlags::Persistent)) {
			PState->SetBindingValueByName(TEXT("$ptype"), Name);
			if (PState->Step() == ESQLitePreparedStatementStepResult::Row) {
				PState->GetColumnValueByIndex(0, HP);
			}
		}

		PState->Destroy();
		delete PState;
	}
	Database->Close();
	delete Database;

	return HP;
}

void UDataLoadManager::LoadMonsterDropItem(FString Name)
{
	FString Ptype = TEXT("");

	Database = new FSQLiteDatabase();

	const FString Path = FPaths::ProjectContentDir() + "Database/datasheet.db";
	if (Database->Open(*Path, ESQLiteDatabaseOpenMode::ReadWrite)) {

		PState = new FSQLitePreparedStatement();

		const TCHAR* LoadQuery = TEXT("select ptype from item where id in (select itemId from drops where monsterId = (select id from monster where ptype = $ptype));");
		if (PState->Create(*Database, LoadQuery, ESQLitePreparedStatementFlags::Persistent)) {
			PState->SetBindingValueByName(TEXT("$ptype"), Name);
			while (PState->Step() == ESQLitePreparedStatementStepResult::Row) {
				PState->GetColumnValueByIndex(0, Ptype);
			}
		}

		PState->Destroy();
		delete PState;
	}
	Database->Close();
	delete Database;
}

FString UDataLoadManager::LoadItem(FString Name)
{
	FString Description = TEXT("");

	Database = new FSQLiteDatabase();

	const FString Path = FPaths::ProjectContentDir() + "Database/datasheet.db";
	if (Database->Open(*Path, ESQLiteDatabaseOpenMode::ReadWrite)) {

		PState = new FSQLitePreparedStatement();

		const TCHAR* LoadQuery = TEXT("select descript from item where ptype = $ptype;");
		if (PState->Create(*Database, LoadQuery, ESQLitePreparedStatementFlags::Persistent)) {
			PState->SetBindingValueByName(TEXT("$ptype"), Name);
			while (PState->Step() == ESQLitePreparedStatementStepResult::Row) {
				PState->GetColumnValueByIndex(0, Description);
			}
		}

		PState->Destroy();
		delete PState;
	}
	Database->Close();
	delete Database;

	return Description;
}
