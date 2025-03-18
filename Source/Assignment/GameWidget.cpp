// Fill out your copyright notice in the Description page of Project Settings.


#include "GameWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

void UGameWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (SubmitButton)SubmitButton->OnClicked.AddDynamic(this, &UGameWidget::OnClickedSubmitButton);
	if (BackspaceButton)BackspaceButton->OnClicked.AddDynamic(this, &UGameWidget::OnClickedBackspaceButton);
	if (NumButton1)NumButton1->OnClicked.AddDynamic(this, &UGameWidget::OnClickedNumButton1);
	if (NumButton2)NumButton2->OnClicked.AddDynamic(this, &UGameWidget::OnClickedNumButton2);
	if (NumButton3)NumButton3->OnClicked.AddDynamic(this, &UGameWidget::OnClickedNumButton3);
	if (NumButton4)NumButton4->OnClicked.AddDynamic(this, &UGameWidget::OnClickedNumButton4);
	if (NumButton5)NumButton5->OnClicked.AddDynamic(this, &UGameWidget::OnClickedNumButton5);
	if (NumButton6)NumButton6->OnClicked.AddDynamic(this, &UGameWidget::OnClickedNumButton6);
	if (NumButton7)NumButton7->OnClicked.AddDynamic(this, &UGameWidget::OnClickedNumButton7);
	if (NumButton8)NumButton8->OnClicked.AddDynamic(this, &UGameWidget::OnClickedNumButton8);
	if (NumButton9)NumButton9->OnClicked.AddDynamic(this, &UGameWidget::OnClickedNumButton9);

	PlayerNumString = "   "; // 빈칸 3개
	UpdateOtherNum(PlayerNumString);
	UpdatePlayerNum(PlayerNumString);
}

void UGameWidget::UpdateOtherNum(const FText &Text)
{
	if (OtherNumText)
	{
		OtherNumText->SetText(Text);
	}
}

void UGameWidget::UpdateOtherNum(const FString &String)
{
	UpdateOtherNum(FText::FromString(String));
}

void UGameWidget::UpdatePlayerNum(const FText& Text)
{
	if (PlayerNumText)
	{
		PlayerNumText->SetText(Text);
	}
	OnPlayerTextChanged.Broadcast(Text.ToString());
}

void UGameWidget::UpdatePlayerNum(const FString& String)
{
	UpdatePlayerNum(FText::FromString(String));
}

void UGameWidget::OnClickedSubmitButton()
{
	OnPlayerTextSubmitted.Broadcast(PlayerNumString);
}

void UGameWidget::OnClickedBackspaceButton()
{
	for (int i = 2; i >= 0; i--)
	{
		if (PlayerNumString[i] != ' ')
		{
			PlayerNumString[i] = ' ';
			break;
		}
	}
	UpdatePlayerNum(PlayerNumString);
}

void UGameWidget::OnClickedNumButton1()
{
	AddPlayerNum(1);
}

void UGameWidget::OnClickedNumButton2()
{
	AddPlayerNum(2);
}

void UGameWidget::OnClickedNumButton3()
{
	AddPlayerNum(3);
}

void UGameWidget::OnClickedNumButton4()
{
	AddPlayerNum(4);
}

void UGameWidget::OnClickedNumButton5()
{
	AddPlayerNum(5);
}

void UGameWidget::OnClickedNumButton6()
{
	AddPlayerNum(6);
}

void UGameWidget::OnClickedNumButton7()
{
	AddPlayerNum(7);
}

void UGameWidget::OnClickedNumButton8()
{
	AddPlayerNum(8);
}

void UGameWidget::OnClickedNumButton9()
{
	AddPlayerNum(9);
}

void UGameWidget::AddPlayerNum(const int32 Num)
{
	for (int i = 0; i < 3; i++)
	{
		if (PlayerNumString[i] == ' ')
		{
			PlayerNumString[i] = Num + '0';
			break;
		}
	}
	UpdatePlayerNum(PlayerNumString);
}
