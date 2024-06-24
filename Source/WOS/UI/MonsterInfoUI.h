// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MonsterInfoUI.generated.h"

/**
 * 
 */
UCLASS()
class WOS_API UMonsterInfoUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void NativeConstruct();
	UFUNCTION()
	void SetHP(float curHP, float maxHP);

private:
	UPROPERTY(meta=(BindWidget))
	class UTextBlock* TName;
	UPROPERTY(meta=(BindWidget))
	class UProgressBar* HPBar;
};
