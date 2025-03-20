// Fill out your copyright notice in the Description page of Project Settings.


#include "AssignmentGameMode.h"

#include "AssignmentGameState.h"
#include "AssignmentPlayerController.h"

AAssignmentGameMode::AAssignmentGameMode()
{
	PlayerControllerClass = AAssignmentPlayerController::StaticClass();
	GameStateClass = AAssignmentGameState::StaticClass();

	TurnTimerDuration = 15;
	GameStartDuration = 5;
	GameOverDuration = 5;
}

void AAssignmentGameMode::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle,this, &AAssignmentGameMode::InitializeGame, GameStartDuration, false);
}

void AAssignmentGameMode::GotPlayerNumFromClient(const int32 &PlayerId, const FString& PlayerNumString)
{
	if (AAssignmentGameState *AssignmentGameState = GetGameState<AAssignmentGameState>())
	{
		if (AAssignmentPlayerController* OtherPlayerController = AssignmentGameState->GetOtherPlayer())
		{
			OtherPlayerController->ClientUpdateOtherPlayerNum(PlayerNumString);
		}
		
	}
}

void AAssignmentGameMode::GotSubmitFromClient(const int32& PlayerId, const FString& PlayerNumString)
{
	if (AAssignmentGameState* AssignmentGameState = GetGameState<AAssignmentGameState>())
	{
		// 제출한 플레이어 아이디와 서버의 현재 플레이어 아이디와 불일치 할시 리턴,
		if (AssignmentGameState->GetCurrentPlayer()->GetUniqueID() != PlayerId)
		{
			return;
		}
		
		// 숫자야구 로직
		int32 StrikeCount = 0, BallCount = 0;
		FString Number = AssignmentGameState->GetNumber();
		for (int32 i = 0; i < Number.Len(); i++)
		{
			if (Number[i] == PlayerNumString[i])
			{
				StrikeCount++;
				continue;
			}

			for (int32 j = 0; j < Number.Len(); j++)
			{
				if (i == j) continue;
				if (Number[i] == PlayerNumString[j])
				{
					BallCount++;
					break;
				}
			}
		}
		
		EndTurn(StrikeCount, BallCount);
	}
}

void AAssignmentGameMode::InitializeGame()
{
	if (AAssignmentGameState* AssignmentGameState = GetGameState<AAssignmentGameState>())
	{
		// 숫자 랜덤 생성 후 서버 게임 스테이트에만 저장
		AssignmentGameState->SetNumber(GenerateNumber());

		// 서버 게임 스테이트에 플레이어 등록 및 초기화{PlayerID, TurnCount}
		for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
		{
			if (AAssignmentPlayerController* PlayerController = Cast<AAssignmentPlayerController>(*It))
			{
				PlayerController->ClientInitializeGame();
				int32 PlayerId = PlayerController->GetUniqueID();
				AssignmentGameState->AddPlayerRemainTurn(PlayerId, 3);

				// 서버 게임 스테이트에 플레이어 할당
				if (!AssignmentGameState->GetCurrentPlayer())
				{
					AssignmentGameState->SetCurrentPlayer(PlayerController);
				}
				else if (!AssignmentGameState->GetOtherPlayer())
				{
					AssignmentGameState->SetOtherPlayer(PlayerController);
				}
			}
		}
		// 플레이어 턴 랜덤 지정
		if (FMath::RandBool())
		{
			AssignmentGameState->SwapPlayerController();
		}
		// 현재 플레이어 턴 시작
		PlayerStartTurn(AssignmentGameState->GetCurrentPlayer());
	}
	
}

FString AAssignmentGameMode::GenerateNumber()
{
	TArray<FString> Nums = {"1", "2", "3", "4", "5", "6", "7", "8", "9" };
	Nums.Sort([](const FString &A, const FString &B){return FMath::RandBool();}); // 배열 랜덤으로 섞어버리기
	return Nums[0] + Nums[1] + Nums[2];
}

void AAssignmentGameMode::EndTurn(const int32 &StrikeCount, const int32 &BallCount)
{
	// 타이머 실행 중이면 클리어
	if (TurnTimer.IsValid())
	{
		GetWorldTimerManager().ClearTimer(TurnTimer);
	}
	
	if (AAssignmentGameState* AssignmentGameState = GetGameState<AAssignmentGameState>())
	{
		bool bIsTurnStarted = false;
		AAssignmentPlayerController* CurrentPlayerController = AssignmentGameState->GetCurrentPlayer();
		AAssignmentPlayerController* OtherPlayerController = AssignmentGameState->GetOtherPlayer();

		if (CurrentPlayerController && OtherPlayerController)
		{
			// 결과 업데이트
			CurrentPlayerController->ClientUpdateSubmitResult(StrikeCount, BallCount);
			OtherPlayerController->ClientUpdateSubmitResult(StrikeCount, BallCount);
			
			if (StrikeCount < 3)
			{
				// 현재 진행중인 플레이어의 턴 종료
				PlayerEndTurn(CurrentPlayerController);
				// 현재 진행중 플레이어 교체 및 플레이어 턴 시작
				bIsTurnStarted = PlayerStartTurn(OtherPlayerController);
			}
			else
			{
				CurrentPlayerController->ClientPlayerWin();
				OtherPlayerController->ClientPlayerLose();
				GameOver();
				return;
			}
			
			// 턴이 시작되지 않으면 Draw 호출
			if (bIsTurnStarted == false)
			{
				CurrentPlayerController->ClientPlayerDraw();
				OtherPlayerController->ClientPlayerDraw();
				GameOver();
			}
		}
	}
}

bool AAssignmentGameMode::PlayerStartTurn(AAssignmentPlayerController* PlayerController)
{
	if (AAssignmentGameState* AssignmentGameState = GetGameState<AAssignmentGameState>())
	{
		if (AssignmentGameState->GetRemainTurn(PlayerController->GetUniqueID()) > 0)
		{
			PlayerController->ClientStartTurn();

			// 타이머 시작
			RemainTime = TurnTimerDuration;
			UpdateRemainTimePlayers();
			GetWorldTimerManager().SetTimer(TurnTimer, this, &AAssignmentGameMode::TurnTimerLoop, 1.0f, true);
			return true;
		}
	}
	return false;
}

void AAssignmentGameMode::PlayerEndTurn(AAssignmentPlayerController* PlayerController)
{
	if (AAssignmentGameState* AssignmentGameState = GetGameState<AAssignmentGameState>())
	{
		// 현재 플레이어 남은 횟수 감소
		const int32 PlayerId = PlayerController->GetUniqueID();
		AssignmentGameState->DecreaseRemainTurn(PlayerId);

		// 현재 플레이어에게 턴 종료 알림
		PlayerController->ClientEndTurn(AssignmentGameState->GetRemainTurn(PlayerId));

		// 턴 종료 후 플레이어 스왑
		AssignmentGameState->SwapPlayerController();
	}
}

void AAssignmentGameMode::TurnTimerLoop()
{
	if (RemainTime > 0)
	{
		RemainTime -= 1.0f;
		UpdateRemainTimePlayers();
	}
	else
	{
		GetWorldTimerManager().ClearTimer(TurnTimer);
		EndTurn();
	}
}

void AAssignmentGameMode::UpdateRemainTimePlayers()
{
	for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
	{
		if (AAssignmentPlayerController* PlayerController = Cast<AAssignmentPlayerController>(*It))
		{
			PlayerController->ClientUpdateTimer(RemainTime);
		}
	}
}

void AAssignmentGameMode::GameOver()
{
	// GameOver 3초 대기 후 게임 초기화
	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AAssignmentGameMode::InitializeGame, GameOverDuration, false);
}
