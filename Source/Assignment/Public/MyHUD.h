// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "UiWidget.h"
#include "MenuWidget.h"
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
	UUiWidget* UiWidget;
	UPROPERTY(EditAnywhere, Category = "UI")
	UMenuWidget* MenuWidget;

	void ShowMenu();
};
