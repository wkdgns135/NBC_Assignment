// Fill out your copyright notice in the Description page of Project Settings.


#include "AssignmentPlayerController.h"

#include "AssignmentGameMode.h"
#include "GameWidget.h"
#include "Blueprint/UserWidget.h"

void AAssignmentPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (IsLocalController())
	{
		if (GameWidget)
		{
			GameWidget->AddToViewport();
			GameWidget->SetVisibility(ESlateVisibility::Visible);
			GameWidget->OnPlayerTextChanged.AddUObject(this, &AAssignmentPlayerController::ServerUpdatePlayerNum);
		}
	}
}

void AAssignmentPlayerController::ServerUpdatePlayerNum_Implementation(const FString& PlayerNumString)
{
	if (AAssignmentGameMode* GameMode = Cast<AAssignmentGameMode>(GetWorld()->GetAuthGameMode()))
	{
		GameMode->GotPlayerNumFromClient(GetUniqueID(), PlayerNumString);
	}
}

void AAssignmentPlayerController::ClientUpdateOtherPlayerNum_Implementation(const FString& PlayerNumString)
{
	if (GameWidget)
	{
		GameWidget->UpdateOtherNum(PlayerNumString);
	}
}
