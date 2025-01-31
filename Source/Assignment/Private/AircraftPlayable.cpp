// Fill out your copyright notice in the Description page of Project Settings.


#include "AircraftPlayable.h"
#include "EnhancedInputComponent.h"

AAircraftPlayable::AAircraftPlayable()
{
	bUseGravity = true;
	Drag = 0.5;
	AngularDrag = 0.9;
	AngularThreshold = 80.0f;
	CameraComponent->SetRelativeLocation(FVector(-50, 0, 200));
	CameraComponent->SetRelativeRotation(FRotator(-20, 0, 0));
}

void AAircraftPlayable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AddLift();
	AddAngularDrag(DeltaTime);
}

void AAircraftPlayable::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (APlayableController* PlayerController = Cast<APlayableController>(GetController()))
		{
			if (PlayerController->RollAction)
			{
				EnhancedInput->BindAction(PlayerController->RollAction, ETriggerEvent::Triggered, this, &AAircraftPlayable::Roll);
			}
		}
	}
}

void AAircraftPlayable::PressSpace(const FInputActionValue& Value)
{
	FVector Up = GetActorUpVector();
	AddForce(Up * MoveScalar * Mass * 2);
}

void AAircraftPlayable::PressShift(const FInputActionValue& Value)
{
	FVector Down = GetActorUpVector() * -1;
	AddForce(Down * MoveScalar * Mass);
}


void AAircraftPlayable::Move(const FInputActionValue& Value)
{
	const FVector2D MoveInput = Value.Get<FVector2D>();
	if (MoveInput.IsNearlyZero()) return;

	FVector Forward = GetActorForwardVector();
	FVector Right = GetActorRightVector();

	// 입력에 따라 이동 벡터 계산
	FVector InputForce = (Forward * MoveInput.X + Right * MoveInput.Y);
	InputForce = InputForce.GetSafeNormal() * MoveScalar;

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
		ActorRotation.Pitch = FMath::Clamp(ActorRotation.Pitch - LookInput.Y, -AngularThreshold, AngularThreshold);
		SetActorRotation(ActorRotation);

		// 2. 컨트롤러 회전값 업데이트
		FRotator ControlRotation = GetControlRotation();
		ControlRotation.Yaw += LookInput.X;
		ControlRotation.Pitch = FMath::Clamp(ControlRotation.Pitch - LookInput.Y, -AngularThreshold, AngularThreshold);
		Controller->SetControlRotation(ControlRotation);
	}
}

void AAircraftPlayable::Roll(const FInputActionValue& Value)
{
	// QE 입력에 따른 Roll 회전
	const float MoveInput = Value.Get<float>();
	FRotator ActorRotation = GetActorRotation();
	ActorRotation.Roll = FMath::Clamp(ActorRotation.Roll + MoveInput, -AngularThreshold, AngularThreshold);
	SetActorRotation(ActorRotation);
}

void AAircraftPlayable::AddLift()
{
	// 양력 추가
	FVector Up = GetActorUpVector();
	AddForce(Up * Gravity * Mass);
}

void AAircraftPlayable::AddAngularDrag(float DeltaTime)
{
	FRotator ActorRotation = GetActorRotation();

	// 각 댐핑 적용
	//ActorRotation.Pitch *= FMath::Pow(1 - AngularDrag, DeltaTime);
	ActorRotation.Roll *= FMath::Pow(1 - AngularDrag, DeltaTime);

	SetActorRotation(ActorRotation);
}