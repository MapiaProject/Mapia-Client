// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LoginFailUI.generated.h"

/**
 * 
 */
UCLASS()
class WOS_API ULoginFailUI : public UUserWidget
{
	GENERATED_BODY()

public:
	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

	UFUNCTION()
	void SetCause(int cause);

	bool isOnFailUI;

private:
	UPROPERTY(meta=(BindWidget))
	class UEditableTextBox* TCause;

	float HoldingTime;
};
