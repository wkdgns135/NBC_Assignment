#include "PatrolActor.h"

APatrolActor::APatrolActor()
{
	PrimaryActorTick.bCanEverTick = true;
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Script/Engine.StaticMesh'/Engine/EditorMeshes/AssetViewer/Floor_Mesh.Floor_Mesh'"));
	if (MeshAsset.Succeeded())
	{
		StaticMeshComponent->SetStaticMesh(MeshAsset.Object);
	}

	PatrolDirection = EDirection::Forward;
	PatrolSpeed = 1000;
	PatrolRange = 1000;
}

void APatrolActor::BeginPlay()
{
	Super::BeginPlay();
	
}

FVector APatrolActor::GetDirection()
{
	if (TotalMoveDistance >= PatrolRange) {
		PatrolDirection = (EDirection)(((int)PatrolDirection + 2) % 4);
		TotalMoveDistance = 0;
	}
	return MovementOffsets[(int)PatrolDirection];
}

void APatrolActor::Patrol(const float DeltaTime)
{
	FVector MovementDelta = GetDirection() * PatrolSpeed * DeltaTime;
	AddActorLocalOffset(MovementDelta);
	TotalMoveDistance += MovementDelta.Length();
}

void APatrolActor::Init(const EDirection Direction, const float Speed, const float Range)
{
	PatrolDirection = Direction;
	PatrolSpeed = Speed;
	PatrolRange = Range;
}


void APatrolActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Patrol(DeltaTime);
}

