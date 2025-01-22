// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DynamicActor.h"
#include "PatrolActor.generated.h"

UENUM()
enum class EDirection {
	Forward,
	Right,
	Backward,
	Left,
};

UCLASS()
class ASSIGNMENT_API APatrolActor : public ADynamicActor
{
	GENERATED_BODY()
	
public:	
	APatrolActor();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = "Properties") EDirection PatrolDirection;
	UPROPERTY(EditAnywhere, Category = "Properties") float PatrolSpeed;
	UPROPERTY(EditAnywhere, Category = "Properties") float PatrolRange;

	FVector MovementOffsets[4] = { {1,0,0},{0,1,0},{-1,0,0},{0,-1,0} };
	float TotalMoveDistance = 0;

	FVector GetDirection();
	void Patrol(const float DeltaTime);

public:
	void Init(const EDirection Direction, const float Speed, const float Range);
};
