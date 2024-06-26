// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LobbyUI.generated.h"

/**
 * 
 */
UCLASS()
class MORALHAZARD_API ULobbyUI : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	void AddRoom(uint32 Id, FStringView Name) const;
protected:
	UPROPERTY(EditAnywhere, Category="Prop")
	TSubclassOf<UUserWidget> RoomButton;
private:
	UPROPERTY(meta=(BindWidget))
	class UVerticalBox* RoomListVerticalBox;
};
