// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DynamicActor.h"
#include "PatrolActor.h"
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
	void GenerateActor();
	void InitializeGrid(TArray<TArray<TPair<EDirection, int>>>& Grid);
	void SetupGraph(TArray<TArray<TPair<EDirection, int>>>& Grid, TMap<TPair<int, int>, TArray<TPair<int, int>>>& Graph);
	bool FindPath(const TMap<TPair<int, int>, TArray<TPair<int, int>>>& Graph, TArray<TPair<int, int>>& Path);
	void SpawnActorsAlongPath(const TArray<TPair<int, int>>& Path, const TArray<TArray<TPair<EDirection, int>>>& Grid);
	
private:
	UPROPERTY(EditAnywhere, Category = "Properties") int Width;
	UPROPERTY(EditAnywhere, Category = "Properties") int Height;
	UPROPERTY(EditAnywhere, Category = "Properties") int MinPatrolRange;
	
};
