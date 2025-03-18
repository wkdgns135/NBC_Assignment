// Fill out your copyright notice in the Description page of Project Settings.


#include "AssignmentGameMode.h"

#include "AssignmentPlayerController.h"

AAssignmentGameMode::AAssignmentGameMode()
{
	PlayerControllerClass = AAssignmentPlayerController::StaticClass();
}

void AAssignmentGameMode::GotPlayerNumFromClient(const int32 &PlayerId, const FString& PlayerNumString)
{
	for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
	{
		AAssignmentPlayerController* PlayerController = Cast<AAssignmentPlayerController>(*It);
		if (PlayerController && PlayerController->GetUniqueID() != PlayerId)
		{
			PlayerController->ClientUpdateOtherPlayerNum(PlayerNumString);
			break;
		}
	}
}
