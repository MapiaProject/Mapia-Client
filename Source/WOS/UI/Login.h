// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Login.generated.h"

/**
 * 
 */
UCLASS()
class WOS_API ULogin : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void NativeConstruct();
	UFUNCTION()
	void SuccessLogin();

protected:
	UFUNCTION()
	void OnClickStart();
	UFUNCTION()
	void OnClickJoin();

private:
	UPROPERTY(meta=(BindWidget))
	class UEditableTextBox* ID;
	UPROPERTY(meta=(BindWidget))
	class UEditableTextBox* PW;
	UPROPERTY(meta=(BindWidget))
	class UButton* BStart;
	UPROPERTY(meta= (BindWidget))
	class UButton* BJoin;

};
