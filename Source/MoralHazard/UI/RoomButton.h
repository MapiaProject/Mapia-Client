// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RoomButton.generated.h"

/**
 * 
 */
UCLASS()
class MORALHAZARD_API URoomButton : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	
	UFUNCTION()
	void OnClick();
public:
	UPROPERTY(meta=(BindWidget))
	class UButton* RoomButton;
	UPROPERTY(meta=(BindWidget))
	class UTextBlock* RoomName;

	uint32 RoomId;
};
