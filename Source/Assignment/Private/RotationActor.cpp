#include "RotationActor.h"

ARotationActor::ARotationActor()
{
	PrimaryActorTick.bCanEverTick = true;
	bRotateRight = true;
	RotationSpeed = 1000;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Script/Engine.StaticMesh'/Engine/EditorMeshes/AssetViewer/Floor_Mesh.Floor_Mesh'"));
	if (MeshAsset.Succeeded())
	{
		StaticMeshComponent->SetStaticMesh(MeshAsset.Object);
	}
}

void ARotationActor::BeginPlay()
{
	Super::BeginPlay();
}

void ARotationActor::ActorRotation(float DeltaTime)
{
	FRotator DeltaRotation = FRotator::ZeroRotator;
	DeltaRotation.Yaw = RotationSpeed * DeltaTime * (bRotateRight ? 1 : -1);
	AddActorLocalRotation(DeltaRotation);
}

void ARotationActor::Init(const bool bInRotateRight, const float Speed)
{
	bRotateRight = bInRotateRight;
	RotationSpeed = Speed;
}

void ARotationActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ActorRotation(DeltaTime);
}

