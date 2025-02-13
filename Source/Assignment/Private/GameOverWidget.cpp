// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOverWidget.h"
#include "Kismet/GameplayStatics.h"
#include "MyGameInstance.h"

void UGameOverWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Button->OnClicked.AddDynamic(this, &UGameOverWidget::OnButtonButtonClick);

	if (APlayerController* Controller = GetWorld()->GetFirstPlayerController())
	{
		Controller->bShowMouseCursor = true;
		Controller->SetInputMode(FInputModeUIOnly());
	}

	UMyGameInstance* GameInstance = Cast<UMyGameInstance>(GetGameInstance());

	if (GameInstance) {
		int32 Score = Cast<UMyGameInstance>(GetGameInstance())->TotalScore;
		int32 Wave = Cast<UMyGameInstance>(GetGameInstance())->CurrentWave + 1;

		FString ScoreString = FString::Printf(TEXT("Wave : %d, Total Score: %d"), Wave, Score);
		ScoreText->SetText(FText::FromString(ScoreString));
	}
}

void UGameOverWidget::OnButtonButtonClick()
{
	UGameplayStatics::OpenLevel(GetWorld(), "MainMenuLevel");

}
