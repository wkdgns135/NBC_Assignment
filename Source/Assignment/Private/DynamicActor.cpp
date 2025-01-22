#include "DynamicActor.h"

ADynamicActor::ADynamicActor()
{
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComponent->SetupAttachment(SceneRoot);
}

void ADynamicActor::BeginPlay()
{
	Super::BeginPlay();
}

void ADynamicActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
