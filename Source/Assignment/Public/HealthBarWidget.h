// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "../TP_ThirdPerson/TP_ThirdPersonCharacter.h"
#include "HealthBarWidget.generated.h"

/**
 * 
 */
UCLASS()
class ASSIGNMENT_API UHealthBarWidget : public UUserWidget
{
	GENERATED_BODY()
	
private:
	UPROPERTY(meta = (BindWidget))
	UProgressBar *ProgressBar;
	ATP_ThirdPersonCharacter* Player;

protected:
	virtual void NativeConstruct() override;

public:
	UFUNCTION()
	void OnHealthUpdated(float NewHealth);
};
