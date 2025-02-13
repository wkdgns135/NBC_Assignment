// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "WaveDataRow.h"
#include "MyGameState.generated.h"

class ABaseItem;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnWaveChanged, int32);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnScoreChanged, int32);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnTimeChanged, int32);

UCLASS()
class ASSIGNMENT_API AMyGameState : public AGameState
{
	GENERATED_BODY()

public:
	AMyGameState();
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Wave")
	UDataTable* WaveDataTable;
	UPROPERTY(EditAnywhere, Category = "Wave")
	TSubclassOf<ABaseItem> CoinClass;

	FOnWaveChanged OnWaveChanged;
	FOnScoreChanged OnScoreChanged;
	FOnTimeChanged OnTimeChanged;
	FWaveDataRow* CurrentWaveData;
	FTimerHandle LevelTimerHandle;
	int32 CurrentWaveIndex;
	int32 Score;
	int32 SpawnedCoinCount;
	int32 CollectedCoinCount;

	UFUNCTION(BlueprintPure, Category = "Score")
	int32 GetScore() const;
	UFUNCTION(BlueprintCallable, Category = "Score")
	void AddScore(int32 Amount);
	UFUNCTION(BlueprintCallable, Category = "Wave")
	void OnGameOver();

	void InitWave();
	void StartWave();
	void OnWaveTimeUp();
	void OnTimerTick();
	void OnCoinCollected();
	void EndWave();

private:
	class ASpawnVolume *SpawnVolume;
	int32 CurrentTime;
};
