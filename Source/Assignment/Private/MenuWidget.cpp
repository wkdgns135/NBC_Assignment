// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuWidget.h"
#include "Kismet/GameplayStatics.h"

void UMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	RestartButton->OnClicked.AddDynamic(this, &UMenuWidget::OnRestartButtonClick);
	ExitButton->OnClicked.AddDynamic(this, &UMenuWidget::OnExitButtonClick);
	CloseButton->OnClicked.AddDynamic(this, &UMenuWidget::OnCloseButtonClick);

	if (APlayerController* Controller = GetWorld()->GetFirstPlayerController()) {
		Controller->bShowMouseCursor = true;
		Controller->SetInputMode(FInputModeUIOnly());
	}
}

void UMenuWidget::NativeDestruct()
{
	Super::NativeDestruct();
	RestartButton->OnClicked.RemoveDynamic(this, &UMenuWidget::OnRestartButtonClick);
	ExitButton->OnClicked.RemoveDynamic(this, &UMenuWidget::OnExitButtonClick);
	CloseButton->OnClicked.RemoveDynamic(this, &UMenuWidget::OnCloseButtonClick);

	if (APlayerController* Controller = GetWorld()->GetFirstPlayerController()) {
		Controller->bShowMouseCursor = false;
		Controller->SetInputMode(FInputModeGameOnly());
	}
}

void UMenuWidget::OnRestartButtonClick()
{
	OnRestarted.Broadcast();
	UGameplayStatics::OpenLevel(GetWorld(), "MainLevel");
}

void UMenuWidget::OnExitButtonClick()
{
	UGameplayStatics::OpenLevel(GetWorld(), "MainMenuLevel");
}

void UMenuWidget::OnCloseButtonClick()
{
	ShowHideToggle();
}

void UMenuWidget::ShowHideToggle()
{
	if (IsInViewport())
	{
		RemoveFromViewport();
	}
	else
	{
		AddToViewport();
	}
}