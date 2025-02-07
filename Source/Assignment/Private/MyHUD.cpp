// Fill out your copyright notice in the Description page of Project Settings.


#include "MyHUD.h"
#include "MyGameState.h"

void AMyHUD::BeginPlay()
{
	Super::BeginPlay();
	if (MyUi)
	{
		MyUi->AddToViewport();
	}

	AMyGameState* GameState = GetWorld()->GetGameState<AMyGameState>();
	if (GameState)
	{
		GameState->OnWaveChanged.AddDynamic(this, &AMyHUD::OnWaveUpdated);
		GameState->OnScoreChanged.AddDynamic(this, &AMyHUD::OnScoreUpdated);
		GameState->OnTimeChanged.AddDynamic(this, &AMyHUD::OnTimeUpdated);
	}
}

void AMyHUD::OnWaveUpdated(int32 NewWave)
{
	FString WaveString = FString::Printf(TEXT("Wave: %d"), NewWave);
	MyUi->WaveText->SetText(FText::FromString(WaveString));
}

void AMyHUD::OnScoreUpdated(int32 NewScore)
{
	FString ScoreString = FString::Printf(TEXT("Score: %d"), NewScore);
	MyUi->ScoreText->SetText(FText::FromString(ScoreString));
}

void AMyHUD::OnTimeUpdated(float RemainingTime)
{
	FString TimeString = FString::Printf(TEXT("Time: %d"), RemainingTime);
	MyUi->TimeText->SetText(FText::FromString(TimeString));
}

void AMyHUD::OnHealthUpdated(float NewHealth)
{
	FString HealthString = FString::Printf(TEXT("Hp: %d"), NewHealth);
	MyUi->HealthText->SetText(FText::FromString(HealthString));
}
