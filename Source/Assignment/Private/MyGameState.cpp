#include "MyGameState.h"
#include "Kismet/GameplayStatics.h"
#include "SpawnVolume.h"
#include "ItemCoin.h"

AMyGameState::AMyGameState()
{
	Score = 0;
	SpawnedCoinCount = 0;
	CollectedCoinCount = 0;
	CurrentWaveIndex = 0;
}

void AMyGameState::BeginPlay()
{
	Super::BeginPlay();
	InitWave();
	StartWave();
}

int32 AMyGameState::GetScore() const
{
	return Score;
}

void AMyGameState::AddScore(int32 Amount)
{
	Score += Amount;
	OnScoreChanged.Broadcast(Score);
}

void AMyGameState::InitWave()
{
	TArray<FName> RowNames = WaveDataTable->GetRowNames();
	if (RowNames.IsEmpty())return;

	static const FString ContextString(TEXT("WaveDataContext"));
	CurrentWaveData = WaveDataTable->FindRow<FWaveDataRow>(RowNames[CurrentWaveIndex], ContextString);
}

void AMyGameState::StartWave()
{
	SpawnedCoinCount = 30;
	CollectedCoinCount = 30;

	TArray<AActor*> FoundVolumes;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnVolume::StaticClass(), FoundVolumes);

	if (!FoundVolumes.IsEmpty()) {
		ASpawnVolume* SpawnVolume = Cast<ASpawnVolume>(FoundVolumes[0]);
		if (SpawnVolume) {
			for (int32 i = 0; i < CurrentWaveData->PositiveItem; i++)
			{
				AActor* SpawnedActor = SpawnVolume->SpawnRandomItem(true);
			}
			for (int32 i = 0; i < CurrentWaveData->NegativeItem; i++)
			{
				AActor* SpawnedActor = SpawnVolume->SpawnRandomItem(false);
			}
			for (int32 i = 0; i < CurrentWaveData->CoinSpawn; i++)
			{
				AActor* SpawnedActor = SpawnVolume->SpawnItem(CoinClass->StaticClass());
				if (SpawnedActor)
				{
					int32 CoinValue = FMath::RandRange(CurrentWaveData->CoinValueRange.X, CurrentWaveData->CoinValueRange.Y);
					Cast<AItemCoin>(SpawnedActor)->SetPointValue(CoinValue);
				}
			}
		}
	}

	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("Wave : %d Start"), CurrentWaveIndex + 1));

	GetWorldTimerManager().SetTimer(
		LevelTimerHandle,
		this,
		&AMyGameState::OnWaveTimeUp,
		CurrentWaveData->WaveDuration,
		false
	);
}

void AMyGameState::OnWaveTimeUp()
{
	EndWave();
}

void AMyGameState::OnCoinCollected()
{
	CollectedCoinCount++;

	UE_LOG(LogTemp, Warning, TEXT("Coin Collected: %d / %d"),
		CollectedCoinCount,
		SpawnedCoinCount)

		if (SpawnedCoinCount > 0 && CollectedCoinCount >= SpawnedCoinCount)
		{
			EndWave();
		}
}

void AMyGameState::EndWave()
{
	GetWorldTimerManager().ClearTimer(LevelTimerHandle);

	CurrentWaveIndex++;
	OnWaveChanged.Broadcast(CurrentWaveIndex);

	if (CurrentWaveIndex >= WaveDataTable->GetRowNames().Num()) {
		OnGameOver();
		return;
	}

	InitWave();
	StartWave();
}

void AMyGameState::OnGameOver()
{
	UE_LOG(LogTemp, Warning, TEXT("Game Over!!"));
}