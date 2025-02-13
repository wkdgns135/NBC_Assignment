// Fill out your copyright notice in the Description page of Project Settings.


#include "MyHUD.h"
#include "MyGameState.h"

void AMyHUD::BeginPlay()
{
	Super::BeginPlay();
	if (UiWidget)
	{
		UiWidget->AddToViewport();
	}
}

void AMyHUD::ShowMenu()
{
	if (MenuWidget) 
	{
		MenuWidget->ShowHideToggle();
	}
}
