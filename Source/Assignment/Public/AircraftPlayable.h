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

	virtual void PressShift(const FInputActionValue& Value) override;
	virtual void PressSpace(const FInputActionValue& Value) override;
	virtual void Move(const FInputActionValue& Value) override;
	virtual void Look(const FInputActionValue& Value) override;

	void ReleaseShift(const FInputActionValue& Value);
};
