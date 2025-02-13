// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuWidget.h"
#include "Kismet/GameplayStatics.h"

void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	GameStartButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnGameStartButtonClick);
	ExitButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnExitButtonClick);

	if (APlayerController* Controller = GetWorld()->GetFirstPlayerController()) 
	{
		Controller->bShowMouseCursor = true;
		Controller->SetInputMode(FInputModeUIOnly());
	}
		
}

void UMainMenuWidget::NativeDestruct()
{
	if (APlayerController* Controller = GetWorld()->GetFirstPlayerController())
	{
		Controller->bShowMouseCursor = false;
		Controller->SetInputMode(FInputModeGameOnly());
	}
}

void UMainMenuWidget::OnGameStartButtonClick()
{
	UGameplayStatics::OpenLevel(GetWorld(), "MainLevel");
}

void UMainMenuWidget::OnExitButtonClick()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), UGameplayStatics::GetPlayerController(GetWorld(), 0), EQuitPreference::Quit, true);
}
