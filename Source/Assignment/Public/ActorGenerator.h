// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DynamicActor.h"
#include "ActorGenerator.generated.h"

UCLASS()
class ASSIGNMENT_API AActorGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	AActorGenerator();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere) int Width;
	UPROPERTY(EditAnywhere) int Height;
	UPROPERTY(EditAnywhere) int MinPatrolRange;
	
	void GenerateActor();

};
