#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DynamicActor.h"
#include "RotationActor.generated.h"

UCLASS()
class ASSIGNMENT_API ARotationActor : public ADynamicActor
{
	GENERATED_BODY()
	
public:	
	ARotationActor();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = "Properties") bool bRotateRight;
	UPROPERTY(EditAnywhere, Category = "Properties") float RotationSpeed;

	void ActorRotation(float DeltaTime);

public:
	void Init(const bool bRotateRight, const float Speed);
};