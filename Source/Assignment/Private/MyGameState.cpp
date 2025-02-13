#include "MyGameState.h"
#include "Kismet/GameplayStatics.h"
#include "SpawnVolume.h"
#include "ItemCoin.h"
#include "MyGameInstance.h"

AMyGameState::AMyGameState()
{
	SpawnedCoinCount = 0;
	CollectedCoinCount = 0;
	CurrentTime = 0;
}

void AMyGameState::BeginPlay()
{
	Super::BeginPlay();

	GameInstance = Cast<UMyGameInstance>(GetGameInstance());
	GameInstance->CurrentWave = 0;
	GameInstance->TotalScore = 0;

	TArray<AActor*> FoundVolumes;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnVolume::StaticClass(), FoundVolumes);
	if (!FoundVolumes.IsEmpty()) {
		SpawnVolume = Cast<ASpawnVolume>(FoundVolumes[0]);
	}

	InitWave();
	StartWave();

	OnScoreChanged.Broadcast(GameInstance->TotalScore);
	OnWaveChanged.Broadcast(GameInstance->CurrentWave + 1);
}

void AMyGameState::AddScore(int32 Amount)
{
	GameInstance->TotalScore += Amount;
	OnScoreChanged.Broadcast(GameInstance->TotalScore);
}

void AMyGameState::InitWave()
{
	TArray<FName> RowNames = WaveDataTable->GetRowNames();
	if (RowNames.IsEmpty()) return;
	static const FString ContextString(TEXT("WaveDataContext"));
	CurrentWaveData = WaveDataTable->FindRow<FWaveDataRow>(RowNames[GameInstance->CurrentWave], ContextString);
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
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("Wave : %d Start"), GameInstance->CurrentWave + 1));

	GetWorldTimerManager().SetTimer(
		LevelTimerHandle,
		this,
		&AMyGameState::OnTimerTick,
		1,
		true
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

	if (CurrentTime == CurrentWaveData->WaveDuration)
	{
		OnWaveTimeUp();
	}
}

void AMyGameState::EndWave()
{
	GameInstance->CurrentWave++;
	OnWaveChanged.Broadcast(GameInstance->CurrentWave + 1);

	if (GameInstance->CurrentWave >= WaveDataTable->GetRowNames().Num()) {
		OnGameOver();
		return;
	}

	InitWave();
	StartWave();
}

void AMyGameState::OnGameOver()
{
	// Timer 종료 -> Wave 종료 Clear Timer -> 타이머 시작 
	GetWorldTimerManager().ClearTimer(LevelTimerHandle);
	UGameplayStatics::OpenLevel(GetWorld(), "GameOverLevel");
}
