// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "MenuWidget.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnRestarted)

UCLASS()
class ASSIGNMENT_API UMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

public:
	UPROPERTY(meta = (BindWidget))
	UButton* RestartButton;
	UPROPERTY(meta = (BindWidget))
	UButton* ExitButton;
	UPROPERTY(meta = (BindWidget))
	UButton* CloseButton;

	FOnRestarted OnRestarted;

	UFUNCTION()
	void OnRestartButtonClick();
	UFUNCTION()
	void OnExitButtonClick();
	UFUNCTION()
	void OnCloseButtonClick();

	void ShowHideToggle();
};
