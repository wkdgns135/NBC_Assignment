// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "AssignmentGameState.generated.h"

class AAssignmentPlayerController;

UCLASS()
class ASSIGNMENT_API AAssignmentGameState : public AGameState
{
	GENERATED_BODY()

private:
	FString Number;
	AAssignmentPlayerController *CurrentPlayer;
	AAssignmentPlayerController *OtherPlayer;
	TMap<int32, int32> PlayerRemainTurn;
	
public:
	void AddPlayerRemainTurn(const int32 &PlayerId, const int32 &TurnCount);
	void DecreaseRemainTurn(const int32 &PlayerId);
	void SwapPlayerController();
	
public:
	FORCEINLINE void SetNumber(const FString& GeneratedNumber){Number = GeneratedNumber;}
	FORCEINLINE FString GetNumber(){return Number;}
	FORCEINLINE int32 GetRemainTurn(const int32 &PlayerId){return PlayerRemainTurn[PlayerId];}
	FORCEINLINE void SetCurrentPlayer(AAssignmentPlayerController* PlayerController){CurrentPlayer = PlayerController;}
	FORCEINLINE AAssignmentPlayerController* GetCurrentPlayer(){return CurrentPlayer;}
	FORCEINLINE void SetOtherPlayer(AAssignmentPlayerController* PlayerController){OtherPlayer = PlayerController;}
	FORCEINLINE AAssignmentPlayerController* GetOtherPlayer(){return OtherPlayer;}
};
