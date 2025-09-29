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
	void Init(const bool bInRotateRight, const float Speed);

protected:
	virtual void BeginPlay() override;

private:
	void ActorRotation(float DeltaTime);

private:
	UPROPERTY(EditAnywhere, Category = "Properties") bool bRotateRight;
	UPROPERTY(EditAnywhere, Category = "Properties") float RotationSpeed;
	
};