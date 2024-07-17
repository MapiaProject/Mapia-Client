// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGameUI.h"
#include "Components/ProgressBar.h"
#include "Components/EditableTextBox.h"
#include "Managers/Manager.h"
#include "Managers/UISystem.h"
#include "Managers/Network.h"
#include "generated/mmo/Enum.gen.hpp"
#include "InputCoreTypes.h"
#include "Components/TextBlock.h"
#include "Components/ScrollBox.h"
#include "generated//mmo/Protocol.gen.hpp"

void UInGameUI::NativeConstruct() {
	Super::NativeConstruct();

	TChat->OnTextCommitted.Clear();
	TChat->OnTextCommitted.AddDynamic(this, &UInGameUI::OnChatTextCommited);
}

void UInGameUI::AddChatHistory(FString Message, FLinearColor TextColor) {
	float Width = 300.0f;
	UWidget* ParentWidget = Cast<UWidget>(GetParent());
	if (ParentWidget)
	{
		FVector2D ParentSize = ParentWidget->GetDesiredSize();
		Width = ParentSize.X * 0.2f;
	}
	
	UTextBlock* TextBlock = NewObject<UTextBlock>(Chating);
	TextBlock->SetText(FText::FromString(Message));
	TextBlock->SetColorAndOpacity(TextColor);
	Chating->AddChild(TextBlock);
	Chating->ScrollToEnd();
}

void UInGameUI::ShowInventory() {
	UManager::UI(GetWorld())->ShowWidget(WidgetType::Inventory);
}

void UInGameUI::ShowMenu() {
	UManager::UI(GetWorld())->ShowWidget(WidgetType::Menu);
}

void UInGameUI::ShowHP(float MaxHP, float CurHP) {
	HPBar->SetPercent(CurHP / MaxHP);
	THP->SetText(FText::FromString(FString::Printf(TEXT("%d/%d"), (int)CurHP, (int)MaxHP)));
}

void UInGameUI::OnChatTextCommited(const FText& Text, ETextCommit::Type CommitMethod) {
	if (CommitMethod == ETextCommit::OnEnter) {
		ParseCommand(Text.ToString());
		TChat->SetText(FText::FromString(TEXT("")));
		TChat->SetFocus();
	}
}

void UInGameUI::ParseCommand(FString Command) {
	TArray<FString> Commands;
	Command.ParseIntoArray(Commands, TEXT(" "), true);
	
	if (Commands.Num() == 0) ParseError(0);
	else {
		if (Commands[0] == TEXT("/a")) {
			if (Commands.Num() < 2) ParseError(1);
			else if (Commands.Num() == 2) {
				gen::mmo::Chat Chat;
				Chat.type = gen::mmo::EChatType::All;
				Chat.message = Commands[1];
				UManager::Net()->Send(ServerType::MMO, &Chat);

				AddChatHistory(TEXT("나->전체 : ") + Commands[1], FLinearColor(1, 153 / 255.0f, 0, 1));
			}
			else ParseError(2);
		}
		else if (Commands[0] == TEXT("/l")) {
			if (Commands.Num() < 2) ParseError(1);
			else if (Commands.Num() == 2) {
				gen::mmo::Chat Chat;
				Chat.type = gen::mmo::EChatType::Local;
				Chat.message = Commands[1];
				UManager::Net()->Send(ServerType::MMO, &Chat);

				AddChatHistory(TEXT("나->지역 : ") + Commands[1], FLinearColor(0, 192 / 255.0f, 1, 1));
			}
			else ParseError(2);
		}
		else if (Commands[0] == TEXT("/d")) {
			if (Commands.Num() < 3) ParseError(1);
			else if (Commands.Num() == 3) {
				gen::mmo::Chat Chat;
				Chat.type = gen::mmo::EChatType::Direct;
				Chat.targetName = Commands[1];
				Chat.message = Commands[2];
				UManager::Net()->Send(ServerType::MMO, &Chat);

				AddChatHistory(TEXT("나->") + Commands[1] + TEXT(" : ") + Commands[2], FLinearColor(192 / 255.0f, 32 / 255.0f, 1, 1));
			}
			else ParseError(2);
		}
		else ParseError(0);
	}
}

void UInGameUI::ParseError(int ErrorType) {
	FLinearColor ErrorColor = FLinearColor(1, 0, 0, 1);
	switch (ErrorType) {
	case 0:
		AddChatHistory(TEXT("존재하지 않는 명령어입니다."), ErrorColor);
		break;
	case 1:
		AddChatHistory(TEXT("명령어의 인수가 너무 적습니다."), ErrorColor);
		break;
	case 2:
		AddChatHistory(TEXT("명령어의 인수가 너무 많습니다."), ErrorColor);
		break;
	case 3:
		AddChatHistory(TEXT("존재하지 않는 아이디 입니다."), ErrorColor);
		break;
	}
}