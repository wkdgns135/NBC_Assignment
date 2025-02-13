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
	CurrentTime = 0;
}

void AMyGameState::BeginPlay()
{
	Super::BeginPlay();

	
	TArray<AActor*> FoundVolumes;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnVolume::StaticClass(), FoundVolumes);
	if (!FoundVolumes.IsEmpty()) {
		SpawnVolume = Cast<ASpawnVolume>(FoundVolumes[0]);
	}

	InitWave();
	StartWave();
	OnScoreChanged.Broadcast(Score);
	OnWaveChanged.Broadcast(CurrentWaveIndex + 1);
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
			AActor* SpawnedActor = SpawnVolume->SpawnItem(CoinClass);
			if (SpawnedActor)
			{
				int32 CoinValue = FMath::RandRange(CurrentWaveData->CoinValueRange.X, CurrentWaveData->CoinValueRange.Y);
				Cast<AItemCoin>(SpawnedActor)->SetPointValue(CoinValue);
			}
		}
	}
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("Wave : %d Start"), CurrentWaveIndex + 1));

	GetWorldTimerManager().SetTimer(
		LevelTimerHandle,
		this,
		&AMyGameState::OnTimerTick,
		1,
		false
	);
}

void AMyGameState::OnWaveTimeUp()
{
	CurrentTime = 0;
	EndWave();
}

void AMyGameState::OnTimerTick()
{
	CurrentTime++;
	OnTimeChanged.Broadcast(CurrentWaveData->WaveDuration - CurrentTime);

	if (CurrentTime == CurrentWaveData->WaveDuration) {
		OnWaveTimeUp();
	}
	else {
		GetWorldTimerManager().SetTimer(
			LevelTimerHandle,
			this,
			&AMyGameState::OnTimerTick,
			1,
			false
		);
	}
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
	OnWaveChanged.Broadcast(CurrentWaveIndex + 1);

	if (CurrentWaveIndex >= WaveDataTable->GetRowNames().Num()) {
		OnGameOver();
		return;
	}

	InitWave();
	StartWave();
}

void AMyGameState::OnGameOver()
{
	UGameplayStatics::OpenLevel(GetWorld(), "GameOverLevel");
}