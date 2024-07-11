// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryUI.generated.h"

/**
 * 
 */
UCLASS()
class WOS_API UInventoryUI : public UUserWidget
{
	GENERATED_BODY()

public:
	void NativeConstruct();
	
	UFUNCTION()
	void OnClickDamage();
	UFUNCTION()
	void OnClickSpeed();
	UFUNCTION()
	void OnClickHealth();
	UFUNCTION()
	void OnClickExit();

private:
	UPROPERTY(meta=(BindWidget))
	class UButton* BDamage;
	UPROPERTY(meta = (BindWidget))
	class UButton* BSpeed;
	UPROPERTY(meta = (BindWidget))
	class UButton* BHealth;
	UPROPERTY(meta = (BindWidget))
	class UButton* BExit;
	UPROPERTY(meta = (BindWidget))
	class URichTextBlock* TName;
	
};
