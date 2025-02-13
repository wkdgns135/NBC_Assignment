// Copyright Epic Games, Inc. All Rights Reserved.

#include "TP_ThirdPersonCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"
#include "MyHUD.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

ATP_ThirdPersonCharacter::ATP_ThirdPersonCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	OverheadWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("OverheadWidget"));
	OverheadWidget->SetupAttachment(GetCapsuleComponent());
	OverheadWidget->SetWidgetSpace(EWidgetSpace::Screen);

	MaxHealth = 100;
}

void ATP_ThirdPersonCharacter::BeginPlay()
{
	Super::BeginPlay();
	Health = MaxHealth;
	OnHealthChanged.Broadcast(Health);
}

float ATP_ThirdPersonCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	// 기본 데미지 처리 로직 호출 (필수는 아님)
	float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	AddHealth(-DamageAmount);

	// 체력이 0 이하가 되면 사망 처리
	if (Health <= 0.0f)
	{
		UGameplayStatics::OpenLevel(GetWorld(), "GameOverLevel");
	}

	// 실제 적용된 데미지를 반환
	return ActualDamage;
}

void ATP_ThirdPersonCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATP_ThirdPersonCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ATP_ThirdPersonCharacter::Look);

		EnhancedInputComponent->BindAction(EscAction, ETriggerEvent::Started, this, &ATP_ThirdPersonCharacter::ShowMenu);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void ATP_ThirdPersonCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// Reverse control if the effect is active
		if (bIsControlReversed)
		{
			MovementVector *= -1;
		}

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void ATP_ThirdPersonCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ATP_ThirdPersonCharacter::ShowMenu(const FInputActionValue& Value)
{
	Cast<AMyHUD>(GetWorld()->GetFirstPlayerController()->GetHUD())->ShowMenu();
}

void ATP_ThirdPersonCharacter::AddHealth(int32 Value)
{
	Health = FMath::Clamp(Health + Value, 0, MaxHealth);
	OnHealthChanged.Broadcast(Health);
}

void ATP_ThirdPersonCharacter::ApplySlow(float SlowAmount, float Duration)
{
	OriginalSpeed = GetCharacterMovement()->MaxWalkSpeed;
	GetCharacterMovement()->MaxWalkSpeed *= SlowAmount;
	GetWorldTimerManager().SetTimer(SlowEffectTimerHandle, this, &ATP_ThirdPersonCharacter::RestoreOriginalSpeed, Duration, false);
}

void ATP_ThirdPersonCharacter::RestoreOriginalSpeed()
{
	GetCharacterMovement()->MaxWalkSpeed = OriginalSpeed;
}

void ATP_ThirdPersonCharacter::ApplyBlind(float Duration)
{
	if (bIsBlinded) {
		GetWorldTimerManager().ClearTimer(BlindEffectTimerHandle);
		GetWorldTimerManager().SetTimer(BlindEffectTimerHandle, this, &ATP_ThirdPersonCharacter::EndBlindEffect, Duration, false);
		return;
	}

	bIsBlinded = true;

	if (BlindEffectWidget)
	{
		BlindEffectWidget->AddToViewport();
	}
	
	GetWorldTimerManager().SetTimer(BlindEffectTimerHandle, this, &ATP_ThirdPersonCharacter::EndBlindEffect, Duration, false);
}

void ATP_ThirdPersonCharacter::EndBlindEffect()
{

	if (BlindEffectWidget)
	{
		BlindEffectWidget->RemoveFromViewport();
	}
	
	bIsBlinded = false;
}

void ATP_ThirdPersonCharacter::ApplyReverseControl(float Duration)
{
	if (bIsControlReversed) {
		GetWorldTimerManager().ClearTimer(ReverseControlEffectTimerHandle);
		GetWorldTimerManager().SetTimer(ReverseControlEffectTimerHandle, this, &ATP_ThirdPersonCharacter::EndReverseControlEffect, Duration, false);
		return;
	}
	bIsControlReversed = true;
	GetWorldTimerManager().SetTimer(ReverseControlEffectTimerHandle, this, &ATP_ThirdPersonCharacter::EndReverseControlEffect, Duration, false);
}

void ATP_ThirdPersonCharacter::EndReverseControlEffect()
{
	bIsControlReversed = false;
}