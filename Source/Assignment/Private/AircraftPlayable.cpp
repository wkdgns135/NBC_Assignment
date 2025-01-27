// Fill out your copyright notice in the Description page of Project Settings.


#include "AircraftPlayable.h"
#include "EnhancedInputComponent.h"

AAircraftPlayable::AAircraftPlayable()
{
	bUseGravity = false;
	Drag = 0.8;
	CameraComponent->SetRelativeLocation(FVector(-50, 0, 200));
	CameraComponent->SetRelativeRotation(FRotator(-20, 0, 0));
}

void AAircraftPlayable::PressSpace(const FInputActionValue& Value)
{
	FVector Up = GetActorUpVector();
	AddForce(Up * MoveSpeed);
}

void AAircraftPlayable::PressShift(const FInputActionValue& Value)
{
	FVector Down = GetActorUpVector() * -1;
	AddForce(Down * MoveSpeed);
}


void AAircraftPlayable::Move(const FInputActionValue& Value)
{
	const FVector2D MoveInput = Value.Get<FVector2D>();
	if (MoveInput.IsNearlyZero()) return;

	FVector Forward = GetActorForwardVector();
	FVector Right = GetActorRightVector();

	// 입력에 따라 이동 벡터 계산
	FVector InputForce = (Forward * MoveInput.X + Right * MoveInput.Y);
	InputForce = InputForce.GetSafeNormal() * MoveSpeed;

	// 힘 적용
	AddForce(InputForce * Mass);
}

void AAircraftPlayable::Look(const FInputActionValue& Value)
{
	FVector2D LookInput = Value.Get<FVector2D>();
	if (!LookInput.IsNearlyZero())
	{
		// 1. 현재 캐릭터의 회전값 업데이트
		FRotator ActorRotation = GetActorRotation();
		ActorRotation.Yaw += LookInput.X;
		ActorRotation.Pitch -= LookInput.Y;
		SetActorRotation(ActorRotation);

		// 2. 컨트롤러 회전값 업데이트
		FRotator ControlRotation = GetControlRotation();
		ControlRotation.Yaw += LookInput.X;
		ControlRotation.Pitch = FMath::Clamp(ControlRotation.Pitch - LookInput.Y, -80.0f, 80.0f); // Pitch 제한
		Controller->SetControlRotation(ControlRotation);
	}
}