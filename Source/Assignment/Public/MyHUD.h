// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MyUi.h"
#include "MyHUD.generated.h"

/**
 * 
 */
UCLASS()
class ASSIGNMENT_API AMyHUD : public AHUD
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, Category = "UI")
	UMyUi* MyUi;

	UFUNCTION()
	void OnWaveUpdated(int32 NewWave);
	UFUNCTION()
	void OnScoreUpdated(int32 NewScore);
	UFUNCTION()
	void OnTimeUpdated(float RemainingTime);
	UFUNCTION()
	void OnHealthUpdated(float NewHealth);
};
