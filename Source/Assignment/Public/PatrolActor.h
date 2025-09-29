// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DynamicActor.h"
#include "PatrolActor.generated.h"

UENUM()
enum EDirection {
	EForward = 0,
	ERight = 1,
	EBackward = 2,
	ELeft = 3
};

UCLASS()
class ASSIGNMENT_API APatrolActor : public ADynamicActor
{
	GENERATED_BODY()
	
public:	
	APatrolActor();
	virtual void Tick(float DeltaTime) override;
	void Init(const EDirection Direction, const float Speed, const float Range);

protected:
	virtual void BeginPlay() override;

private:
	FVector GetDirection();
	void Patrol(const float DeltaTime);
	
private:
	constexpr FVector MovementOffsets[4] = { {1,0,0},{0,1,0},{-1,0,0},{0,-1,0} };
	
	UPROPERTY(EditAnywhere, Category = "Properties") EDirection PatrolDirection;
	UPROPERTY(EditAnywhere, Category = "Properties") float PatrolSpeed;
	UPROPERTY(EditAnywhere, Category = "Properties") float PatrolRange;

	float TotalMoveDistance = 0;
};
