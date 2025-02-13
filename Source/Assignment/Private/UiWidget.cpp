// Fill out your copyright notice in the Description page of Project Settings.


#include "UiWidget.h"
#include "MyGameState.h"
#include "../TP_ThirdPerson/TP_ThirdPersonCharacter.h"

void UUiWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (AMyGameState* GameState = GetWorld()->GetGameState<AMyGameState>())
	{
		GameState->OnWaveChanged.AddUObject(this, &UUiWidget::OnWaveUpdated);
		GameState->OnScoreChanged.AddUObject(this, &UUiWidget::OnScoreUpdated);
		GameState->OnTimeChanged.AddUObject(this, &UUiWidget::OnTimeUpdated);
	}

	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		if (APawn* Pawn = PlayerController->GetPawn())
		{
			if (ATP_ThirdPersonCharacter* Player = Cast<ATP_ThirdPersonCharacter>(Pawn))
			{
				Player->OnHealthChanged.AddUObject(this, &UUiWidget::OnHealthUpdated);
			}
		}
	}
}


void UUiWidget::OnWaveUpdated(int32 NewWave)
{
	FString WaveString = FString::Printf(TEXT("Wave: %d"), NewWave);
	WaveText->SetText(FText::FromString(WaveString));
}

void UUiWidget::OnScoreUpdated(int32 NewScore)
{
	FString ScoreString = FString::Printf(TEXT("Score: %d"), NewScore);
	ScoreText->SetText(FText::FromString(ScoreString));
}

void UUiWidget::OnTimeUpdated(int32 RemainingTime)
{
	FString TimeString = FString::Printf(TEXT("Time: %d"), RemainingTime);
	TimeText->SetText(FText::FromString(TimeString));
}

void UUiWidget::OnHealthUpdated(float NewHealth)
{
	FString HealthString = FString::Printf(TEXT("Hp: %d"), static_cast<int>(NewHealth));
	HealthText->SetText(FText::FromString(HealthString));
}