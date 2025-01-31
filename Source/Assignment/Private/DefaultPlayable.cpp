// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultPlayable.h"
#include "EnhancedInputComponent.h"

ADefaultPlayable::ADefaultPlayable()
{
	bUseGravity = true;
	Drag = 0.99f;
	MoveScalar = 1500;
	SprintSpeed = 3000;
}

void ADefaultPlayable::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (APlayableController* PlayerController = Cast<APlayableController>(GetController()))
		{
			if (PlayerController->ShiftAction)
			{
				EnhancedInput->BindAction(PlayerController->ShiftAction, ETriggerEvent::Completed, this, &ADefaultPlayable::ReleaseShift);
			}
		}
	}

}

void ADefaultPlayable::BeginPlay()
{
    Super::BeginPlay();
	OriginSpeed = MoveScalar;
}

void ADefaultPlayable::Move(const FInputActionValue& Value)
{
	const FVector2D MoveInput = Value.Get<FVector2D>();
	if (MoveInput.IsNearlyZero()) return;

	FVector Forward = GetActorForwardVector();
	FVector Right = GetActorRightVector();

	// 입력에 따라 이동 벡터 계산
	FVector InputForce = Forward * MoveInput.X + Right * MoveInput.Y;
	InputForce = InputForce.GetSafeNormal() * MoveScalar;

	//공중에서 속력 제한
	if (!bIsGround) {
		InputForce *= 0.7;
	}
	
	// 힘 적용
	AddForce(InputForce * Mass);
}

void ADefaultPlayable::Look(const FInputActionValue& Value)
{
	FVector2D LookInput = Value.Get<FVector2D>();
	if (!LookInput.IsNearlyZero())
	{
		FRotator ActorRotation = GetActorRotation();
		ActorRotation.Yaw += LookInput.X;
		SetActorRotation(ActorRotation);

		FRotator ControlRotation = GetControlRotation();
		ControlRotation.Yaw += LookInput.X;
		ControlRotation.Pitch = FMath::Clamp(ControlRotation.Pitch - LookInput.Y, -80.0f, 80.0f); // Pitch 제한
		Controller->SetControlRotation(ControlRotation);
	}
}

void ADefaultPlayable::ReleaseShift(const FInputActionValue& Value)
{
	MoveScalar = OriginSpeed;
}


void ADefaultPlayable::PressSpace(const FInputActionValue& Value)
{
    if (bIsGround) {
        bIsGround = false;
        AddForce({ 0,0,JumpScalar * Mass });
    }
}

void ADefaultPlayable::PressShift(const FInputActionValue& Value)
{
	MoveScalar = SprintSpeed;
}
