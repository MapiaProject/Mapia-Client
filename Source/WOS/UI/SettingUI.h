// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SettingUI.generated.h"

/**
 * 
 */
UCLASS()
class WOS_API USettingUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void NativeConstruct();

	UFUNCTION()
	void OnClickLower();
	UFUNCTION()
	void OnClickUpper();
	UFUNCTION()
	void HideSetting();

private:
	UPROPERTY(meta=(BindWidget))
	class UButton* BLower;
	UPROPERTY(meta = (BindWidget))
	class UButton* BUpper;

};
