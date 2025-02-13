// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "GameOverWidget.generated.h"

/**
 * 
 */
UCLASS()
class ASSIGNMENT_API UGameOverWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

public:
	UPROPERTY(meta = (BindWidget))
	UButton* Button;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ScoreText;

	UFUNCTION()
	void OnButtonButtonClick();
};
