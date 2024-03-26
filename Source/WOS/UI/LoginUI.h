// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LoginUI.generated.h"

/**
 * 
 */
UCLASS()
class WOS_API ULoginUI : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
private:
	UFUNCTION()
	void OnClickLogin();
	UFUNCTION()
	void OnClickRegister();

	void Reset();
protected:
	UPROPERTY(meta=(BindWidget))
	class UEditableTextBox* ID;
	UPROPERTY(meta=(BindWidget))
	class UEditableTextBox* Password;
	UPROPERTY(meta=(BindWidget))
	class UButton* RegisterButton;
	UPROPERTY(meta=(BindWidget))
	class UButton* LoginButton;
};
