// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerInfoUI.generated.h"

/**
 * 
 */
UCLASS()
class WOS_API UPlayerInfoUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
	void SetName(FString Name);

private:
	UPROPERTY(meta=(BindWidget))
	class UTextBlock* TName;

};
