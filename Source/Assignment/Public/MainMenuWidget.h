// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "MainMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class ASSIGNMENT_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

public:
	UPROPERTY(meta = (BindWidget))
	UButton* GameStartButton;
	UPROPERTY(meta = (BindWidget))
	UButton* ExitButton;

	UFUNCTION()
	void OnGameStartButtonClick();
	UFUNCTION()
	void OnExitButtonClick();
};
