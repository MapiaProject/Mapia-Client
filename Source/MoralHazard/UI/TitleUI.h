// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TitleUI.generated.h"

/**
 * 
 */
UCLASS()
class MORALHAZARD_API UTitleUI : public UUserWidget
{
	GENERATED_BODY()
private:
	virtual void NativeConstruct() override;
	UFUNCTION()
	void OnClick();
	
	UPROPERTY(meta=(BindWidget))
	class UButton* Background;
};
