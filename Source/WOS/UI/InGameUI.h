// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InGameUI.generated.h"

/**
 * 
 */
UCLASS()
class WOS_API UInGameUI : public UUserWidget
{
	GENERATED_BODY()

public:
	void NativeConstruct();

	UFUNCTION()
	void AddChatHistory(FString Message, FLinearColor TextColor);
	UFUNCTION()
	void SetHP(float MaxHP, float CurHP);
	UFUNCTION()
	void ShowInventory();
	UFUNCTION()
	void ShowMenu();
	
private:
	UPROPERTY(meta=(BindWidget))
	class UProgressBar* HPBar;
	UPROPERTY(meta=(BindWidget))
	class UEditableTextBox* THP;
	UPROPERTY(meta=(BindWidget))
	class UEditableTextBox* TChat;
	UPROPERTY(meta=(BindWidget))
	class UScrollBox* Chating;

	UFUNCTION()
	void OnChatTextCommited(const FText& Text, ETextCommit::Type CommitMethod);
	UFUNCTION()
	void ParseCommand(FString Command);
	UFUNCTION()
	void ParseError(int ErrorType);
};
