// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Playable.h"
#include "DefaultPlayable.generated.h"

/**
 * 
 */
UCLASS()
class ASSIGNMENT_API ADefaultPlayable : public APlayable
{
	GENERATED_BODY()

public:
	ADefaultPlayable();
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void BeginPlay() override;
	virtual void PressSpace(const FInputActionValue& Value) override;
	virtual void PressShift(const FInputActionValue& Value) override;
	virtual void Move(const FInputActionValue& Value) override;
	virtual void Look(const FInputActionValue& Value) override;

private:
	UPROPERTY(EditAnywhere, Category = "Physics") float JumpScalar;
	UPROPERTY(EditAnywhere, Category = "Physics") float SprintSpeed;
	float OriginSpeed;

	UFUNCTION() void ReleaseShift(const FInputActionValue& Value);
};
