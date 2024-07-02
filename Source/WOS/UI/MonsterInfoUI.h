// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MonsterInfoUI.generated.h"

/**
 *
 */
UCLASS(Abstract)
class WOS_API UMonsterInfoUI : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void SetHP(float MaxHP, float CurHP);
	UFUNCTION()
	void SetName(FString Name);

private:
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* HPBar;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TName;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* THP;
};