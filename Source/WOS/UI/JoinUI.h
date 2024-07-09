// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "JoinUI.generated.h"

/**
 * 
 */
UCLASS()
class WOS_API UJoinUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void NativeConstruct();
	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);
	UFUNCTION()
	void IDCheckResult(bool result);
	UFUNCTION()
	void SuccessRegist();

protected:
	UFUNCTION()
	void OnClickIDCheck();
	UFUNCTION()
	void OnClickRegist();
	
private:
	UPROPERTY(meta=(BindWidget))
	class UEditableTextBox* ID;
	UPROPERTY(meta=(BindWidget))
	class UEditableTextBox* PW;
	UPROPERTY(meta=(BindWidget))
	class UEditableTextBox* PWCheck;
	UPROPERTY(meta=(BindWidget))
	class UTextBlock* TIDCheckResult;
	UPROPERTY(meta=(BindWidget))
	class UButton* BIDCheck;
	UPROPERTY(meta=(BindWidget))
	class UButton* BRegist;

	bool isIDCheck;
	bool isPWCheck;

};
