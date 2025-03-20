// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "AssignmentGameMode.generated.h"

class AAssignmentPlayerController;
/**
 * 
 */
UCLASS()
class ASSIGNMENT_API AAssignmentGameMode : public AGameMode
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly)
	float TurnTimerDuration;
	UPROPERTY(EditDefaultsOnly)
	float GameStartDuration;
	UPROPERTY(EditDefaultsOnly)
	float GameOverDuration;
	FTimerHandle TurnTimer;
	float RemainTime;
	
public:
	AAssignmentGameMode();
	void virtual BeginPlay() override;
	
	void GotPlayerNumFromClient(const int32& PlayerId, const FString& PlayerNumString);
	void GotSubmitFromClient(const int32& PlayerId, const FString& PlayerNumString);
	
private:
	void InitializeGame();
	FString GenerateNumber();
	void EndTurn(const int32 &StrikeCount = 0, const int32 &BallCount = 0);
	bool PlayerStartTurn(AAssignmentPlayerController* PlayerController);
	void PlayerEndTurn(AAssignmentPlayerController* PlayerController);
	void TurnTimerLoop();
	void UpdateRemainTimePlayers();
	void GameOver();
};
