#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DynamicActor.generated.h"

UCLASS()
class ASSIGNMENT_API ADynamicActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ADynamicActor();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere) USceneComponent* SceneRoot;
	UPROPERTY(EditAnywhere) UStaticMeshComponent* StaticMeshComponent;

};
