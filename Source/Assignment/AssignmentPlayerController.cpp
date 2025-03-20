// Fill out your copyright notice in the Description page of Project Settings.


#include "AssignmentPlayerController.h"

#include "AssignmentGameMode.h"
#include "AssignmentGameState.h"
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
			GameWidget->OnPlayerTextSubmitted.AddUObject(this, &AAssignmentPlayerController::ServerSubmitPlayerNum);
		}
	}
}

void AAssignmentPlayerController::UpdateRemainTurn(const int32& RemainTurn)
{
	if (GameWidget)
	{
		GameWidget->UpdateRemainTurn(RemainTurn);
	}
}

void AAssignmentPlayerController::ClientUpdateTimer_Implementation(const int32& RemainTime)
{
	if (GameWidget)
	{
		GameWidget->UpdateTimerText(RemainTime);
	}
}

void AAssignmentPlayerController::ClientInitializeGame_Implementation()
{
	if (GameWidget)
	{
		GameWidget->InitializeWidget();
	}
}

void AAssignmentPlayerController::ClientPlayerDraw_Implementation()
{
	if (GameWidget)
	{
		GameWidget->UpdateGameResultText("DRAW");
	}
}

void AAssignmentPlayerController::ClientPlayerWin_Implementation()
{
	if (GameWidget)
	{
		GameWidget->UpdateGameResultText("WIN");
	}
}

void AAssignmentPlayerController::ClientPlayerLose_Implementation()
{
	if (GameWidget)
	{
		GameWidget->UpdateGameResultText("LOSE");
	}
}

void AAssignmentPlayerController::ClientUpdateSubmitResult_Implementation(const int32& StrikeCount, const int32& BallCount)
{
	if (GameWidget)
	{
		GameWidget->UpdateResultText(StrikeCount, BallCount);
	}
}

void AAssignmentPlayerController::ClientEndTurn_Implementation(const int32 CurrentTurn)
{
	if (GameWidget)
	{
		GameWidget->DisableButtons();
		UpdateRemainTurn(CurrentTurn);
	}
}

void AAssignmentPlayerController::ClientStartTurn_Implementation()
{
	if (GameWidget)
	{
		GameWidget->InitializePlayerNum();
		GameWidget->EnableButtons();
	}
}


void AAssignmentPlayerController::ServerSubmitPlayerNum_Implementation(const FString& PlayerNumString)
{
	if (AAssignmentGameMode* GameMode = Cast<AAssignmentGameMode>(GetWorld()->GetAuthGameMode()))
	{
		GameMode->GotSubmitFromClient(GetUniqueID(), PlayerNumString);
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
		GameWidget->UpdateOtherPlayerNum(PlayerNumString);
	}
}