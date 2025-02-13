// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOverWidget.h"
#include "Kismet/GameplayStatics.h"

void UGameOverWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Button->OnClicked.AddDynamic(this, &UGameOverWidget::OnButtonButtonClick);

	if (APlayerController* Controller = GetWorld()->GetFirstPlayerController())
	{
		Controller->bShowMouseCursor = true;
		Controller->SetInputMode(FInputModeUIOnly());
	}
}

void UGameOverWidget::OnButtonButtonClick()
{
	UGameplayStatics::OpenLevel(GetWorld(), "MainMenuLevel");

}
