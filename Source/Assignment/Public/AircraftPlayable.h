// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Playable.h"
#include "AircraftPlayable.generated.h"

/**
 * 
 */
UCLASS()
class ASSIGNMENT_API AAircraftPlayable : public APlayable
{
	GENERATED_BODY()
	
public:
	AAircraftPlayable();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void PressShift(const FInputActionValue& Value) override;
	virtual void PressSpace(const FInputActionValue& Value) override;
	virtual void Move(const FInputActionValue& Value) override;
	virtual void Look(const FInputActionValue& Value) override;

private:
	UPROPERTY(EditAnywhere, Category = "Physics") float AngularDrag;
	UPROPERTY(EditAnywhere, Category = "Physics") float AngularThreshold;

	UFUNCTION() void Roll(const FInputActionValue& Value);

	void AddAngularDrag(float DeltaTime);
	void AddLift();
};
