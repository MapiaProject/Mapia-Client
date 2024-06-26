// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuUI.generated.h"

/**
 * 
 */
UCLASS()
class WOS_API UMenuUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void NativeConstruct();

	UFUNCTION()
	void OnClickSetting();
	UFUNCTION()
	void OnClickLogout();
	UFUNCTION()
	void OnClickLeave();

private:
	UPROPERTY(meta=(BindWidget))
	class UButton* BSetting;
	UPROPERTY(meta = (BindWidget))
	class UButton* BLogout;
	UPROPERTY(meta = (BindWidget))
	class UButton* BLeave;

};
