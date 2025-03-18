// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "AssignmentGameMode.generated.h"

/**
 * 
 */
UCLASS()
class ASSIGNMENT_API AAssignmentGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	AAssignmentGameMode();
	void GotPlayerNumFromClient(const int32& PlayerId, const FString& PlayerNumString);
};
