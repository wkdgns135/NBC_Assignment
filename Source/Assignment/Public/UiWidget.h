// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "UiWidget.generated.h"

/**
 * 
 */
UCLASS()
class ASSIGNMENT_API UUiWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

public:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ScoreText;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* WaveText;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* TimeText;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* HealthText;

	UFUNCTION()
	void OnWaveUpdated(int32 NewWave);
	UFUNCTION()
	void OnScoreUpdated(int32 NewScore);
	UFUNCTION()
	void OnTimeUpdated(int32 RemainingTime);
	UFUNCTION()
	void OnHealthUpdated(float NewHealth);
};
