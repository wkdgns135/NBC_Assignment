// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemCoin.h"
#include "MyGameState.h"

void AItemCoin::ActivateItem(AActor* Activator)
{

	if (UWorld* World = GetWorld())
	{
		if (AMyGameState* GameState = World->GetGameState<AMyGameState>())
		{
			GameState->AddScore(PointValue);
		}
	}

	DestroyItem();
}
