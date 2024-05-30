// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InGameUI.generated.h"

/**
 * 
 */
UCLASS()
class WOS_API UInGameUI : public UUserWidget
{
	GENERATED_BODY()

protected:
	UFUNCTION()
	void ShowInventory();
	UFUNCTION()
	void ShowMenu();
	UFUNCTION()
	void ShowHP(float MaxHP, float CurHP);
	
private:
	UPROPERTY(meta=(BindWidget))
	class UProgressBar* HPBar;
	UPROPERTY(meta=(BindWidget))
	class UEditableTextBox* THP;

};
