// Fill out your copyright notice in the Description page of Project Settings.


#include "AssignmentGameState.h"

void AAssignmentGameState::AddPlayerRemainTurn(const int32& PlayerId, const int32& TurnCount)
{
	PlayerRemainTurn.Add(PlayerId, TurnCount);
}

void AAssignmentGameState::DecreaseRemainTurn(const int32& PlayerId)
{
	if (PlayerRemainTurn.Contains(PlayerId))
	{
		PlayerRemainTurn[PlayerId]--;
	}
}

void AAssignmentGameState::SwapPlayerController()
{
	Swap(CurrentPlayer, OtherPlayer);	
}
