// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "PlayableController.h"
#include "Playable.generated.h"

UCLASS()
class ASSIGNMENT_API APlayable : public APawn
{
	GENERATED_BODY()

public:
	APlayable();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

public:	
	UPROPERTY(VisibleAnywhere, Category = "Character")
	USceneComponent* SceneComponent;
	UPROPERTY(VisibleAnywhere, Category = "Character")
	UCapsuleComponent* CapsuleComponent;
	UPROPERTY(VisibleAnywhere, Category = "Character")
	USkeletalMeshComponent* SkeletalMeshComponent;
	UPROPERTY(VisibleAnywhere, Category = "Camera")
	USpringArmComponent* SpringArmComponent;
	UPROPERTY(VisibleAnywhere, Category = "Camera")
	UCameraComponent* CameraComponent;

	UFUNCTION() virtual void Move(const FInputActionValue& Value) PURE_VIRTUAL(APlayable::Move, ;);
	UFUNCTION() virtual void Look(const FInputActionValue& Value) PURE_VIRTUAL(APlayable::Look, ;);
	UFUNCTION() virtual void PressSpace(const FInputActionValue& Value) PURE_VIRTUAL(APlayable::PressSpace, ;);
	UFUNCTION() virtual void PressShift(const FInputActionValue& Value) PURE_VIRTUAL(APlayable::PressShift, ;);

	void AddForce(FVector ExternalForce);

protected:
	UPROPERTY(EditAnywhere, Category = "Physics") float MoveScalar;
	UPROPERTY(EditAnywhere, Category = "Physics") float Mass;
	UPROPERTY(EditAnywhere, Category = "Physics") float Drag;
	UPROPERTY(EditAnywhere, Category = "Physics") float Gravity;
	bool bIsGround;
	bool bUseGravity;

private:
	FVector Force;
	FVector Velocity;

	void InitConstant();
	void AddGravity();

	// NOTE: Semi-implicit Euler integration 
	// https://en.wikipedia.org/wiki/Semi-implicit_Euler_method ÂüÁ¶
	void Integration(float DeltaTime);
	void HandleCollision(float DeltaTime);
	void UpdatePosition(float DeltaTime);
};
