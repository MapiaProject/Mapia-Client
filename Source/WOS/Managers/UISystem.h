// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Managers/ManagerBase.h"
#include "UISystem.generated.h"

UENUM(BlueprintType)
enum class WidgetType : uint8 {
	Title      UMETA(DisplayName = "Title"),
	Login      UMETA(DisplayName = "Login"),
	LoginFail  UMETA(DisplayName = "LoginFail"),
	Join       UMETA(DisplayName = "Join"),
	InGame     UMETA(DisplayName = "InGame"),
	Inventory  UMETA(DisplayName = "Inventory"),
	Menu       UMETA(DisplayName = "Menu"),
	Setting    UMETA(DisplayName = "Setting")
};

/**
 * 
 */
UCLASS()
class WOS_API UUISystem : public UManagerBase
{
	GENERATED_BODY()

public:

	UFUNCTION()
	void ShowWidget(WidgetType WidgetType);
	UFUNCTION()
	void HideWidget(WidgetType WidgetType);
	UFUNCTION()
	void ExecSuccessLogin();
	UFUNCTION()
	void ExecFailedLogin(int cause);
	UFUNCTION()
	void ExecIDCheckResult(bool Result);
	UFUNCTION()
	void ExecSuccessRegist();
	UFUNCTION()
	void ExecAddChatHistory(FString Message, FLinearColor TextColor);
	UFUNCTION()
	void ExecShowHP(float MaxHP, float CurHP);


	UPROPERTY(EditAnywhere, BlueprintReadWrite) 
	TSubclassOf<class UTitleUI> TitleWidget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) 
	TSubclassOf<class ULoginUI> LoginWidget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class ULoginFailUI> LoginFailWidget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) 
	TSubclassOf<class UJoinUI> JoinWidget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) 
	TSubclassOf<class UInGameUI> InGameWidget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) 
	TSubclassOf<class UInventoryUI> InventoryWidget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) 
	TSubclassOf<class UMenuUI> MenuWidget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) 
	TSubclassOf<class USettingUI> SettingWidget;

	UPROPERTY()
	UUserWidget* TitleWidgetObject;
	UPROPERTY()
	UUserWidget* LoginWidgetObject;
	UPROPERTY()
	UUserWidget* LoginFailWidgetObject;
	UPROPERTY()
	UUserWidget* JoinWidgetObject;
	UPROPERTY()
	UUserWidget* InGameWidgetObject;
	UPROPERTY()
	UUserWidget* InventoryWidgetObject;
	UPROPERTY()
	UUserWidget* MenuWidgetObject;
	UPROPERTY()
	UUserWidget* SettingWidgetObject;
};
