// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Managers/ManagerBase.h"
#include "UISystem.generated.h"

UENUM(BlueprintType)
enum class WidgetType : uint8 {
	Title      UMETA(DisplayName = "Title"),
	Login      UMETA(DisplayName = "Login"),
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
	void ShowWidget(WidgetType widgetType);
	UFUNCTION()
	void HideWidget(WidgetType widgetType);
	UFUNCTION()
	void ExecSuccessLogin();
	UFUNCTION()
	void ExecIDCheckResult(bool result);
	UFUNCTION()
	void ExecSuccessRegist();

	UPROPERTY(EditAnywhere, BlueprintReadWrite) 
	TSubclassOf<UUserWidget> TitleWidget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) 
	TSubclassOf<UUserWidget> LoginWidget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) 
	TSubclassOf<UUserWidget> JoinWidget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) 
	TSubclassOf<UUserWidget> InGameWidget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) 
	TSubclassOf<UUserWidget> InventoryWidget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) 
	TSubclassOf<UUserWidget> MenuWidget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) 
	TSubclassOf<UUserWidget> SettingWidget;

	UUserWidget* TitleWidgetObject;
	UUserWidget* LoginWidgetObject;
	UUserWidget* JoinWidgetObject;
	UUserWidget* InGameWidgetObject;
	UUserWidget* InventoryWidgetObject;
	UUserWidget* MenuWidgetObject;
	UUserWidget* SettingWidgetObject;

};
