// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LoginPopup.generated.h"

/**
 * 
 */
UCLASS()
class WOS_API ULoginPopup : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
public:
	void SetTitle(FText TitleName);
	void SetContent(FText ContentText);
private:
	UFUNCTION()
	void OnClick();
protected:
	UPROPERTY(meta=(BindWidget))
	class UTextBlock* Title;
	UPROPERTY(meta=(BindWidget))
	class UTextBlock* Content;
	UPROPERTY(meta=(BindWidget))
	class UButton* CancelButton;
};
