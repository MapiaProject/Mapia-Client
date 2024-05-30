// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TitleUI.generated.h"

/**
 * 
 */
UCLASS()
class WOS_API UTitleUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void NativeConstruct();

protected:
	UFUNCTION()
	void OnClickStart();

private:
	UPROPERTY(meta=(BindWidget))
	class UButton* BStart;
};
