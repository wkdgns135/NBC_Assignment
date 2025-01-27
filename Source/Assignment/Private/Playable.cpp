// Fill out your copyright notice in the Description page of Project Settings.


#include "Playable.h"
#include "EnhancedInputComponent.h"
#include "DrawDebugHelpers.h"

// Sets default Values
APlayable::APlayable()
{
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collider"));
	SetRootComponent(CapsuleComponent);

	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	SkeletalMeshComponent->SetupAttachment(CapsuleComponent);

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComponent->SetupAttachment(CapsuleComponent);
	SpringArmComponent->TargetArmLength = 400.0f;
	SpringArmComponent->bUsePawnControlRotation = true; // 캐릭터의 회전을 따르도록 설정

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false; // 카메라가 SpringArm의 회전을 따르도록 설정

	InitConstant();
}

void APlayable::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (APlayableController* PlayerController = Cast<APlayableController>(GetController()))
		{
			if (PlayerController->MoveAction)
			{
				EnhancedInput->BindAction(PlayerController->MoveAction, ETriggerEvent::Triggered, this, &APlayable::Move);
			}

			if (PlayerController->SpaceAction)
			{
				EnhancedInput->BindAction(PlayerController->SpaceAction, ETriggerEvent::Triggered, this, &APlayable::PressSpace);
			}

			if (PlayerController->LookAction)
			{
				EnhancedInput->BindAction(PlayerController->LookAction, ETriggerEvent::Triggered, this, &APlayable::Look);
			}

			if (PlayerController->ShiftAction)
			{
				EnhancedInput->BindAction(PlayerController->ShiftAction, ETriggerEvent::Triggered, this, &APlayable::PressShift);
			}
		}
	}
}

void APlayable::BeginPlay()
{
	Super::BeginPlay();

}

void APlayable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AddGravity();
	AddDrag();
	Integration(DeltaTime);
	HandleCollision(DeltaTime);
	UpdatePosition(DeltaTime);
}


void APlayable::AddForce(FVector ExternalForce)
{
	Force += ExternalForce;
}

void APlayable::InitConstant() 
{
	MoveSpeed = 1000;
	Mass = 1;
	Drag = 0.9f;
	Gravity = 980;
	bIsGround = false;
}

void APlayable::AddGravity()
{
	if (!bUseGravity || bIsGround)return;
	FVector GravityForce = FVector(0.0f, 0.0f, -Mass * Gravity);
	AddForce(GravityForce);
}

void APlayable::AddDrag()
{
	// 속도의 제곱에 비례하는 항력 적용
	FVector DragForce = -Drag * Velocity.SizeSquared() * Velocity.GetSafeNormal();
	AddForce(DragForce);
}

void APlayable::Integration(float DeltaTime)
{
	// NOTE: Semi-implicit Euler integration 
	// https://en.wikipedia.org/wiki/Semi-implicit_Euler_method 참조

	// 가속도 계산 (F = ma)
	FVector Acceleration = Force * (1 / Mass);
	Velocity += Acceleration * DeltaTime;

	// 작은 속도는 0으로 설정
	if (Velocity.SizeSquared() < 0.1f)
	{
		Velocity = FVector::ZeroVector;
	}
	// 속도 계산 후 Force 초기화
	Force = FVector::ZeroVector;
}

void APlayable::HandleCollision(float DeltaTime) {
	TArray<FHitResult> HitResults;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);

	float Radius = CapsuleComponent->GetScaledCapsuleRadius();
	float HalfHeight = CapsuleComponent->GetScaledCapsuleHalfHeight();

	// 적분 과정에서 업데이트 된 속도로 다음 위치 예측
	FVector NextPosition = GetActorLocation() + Velocity * DeltaTime; 

	// Sweep 수행
	bool bHit = GetWorld()->SweepMultiByChannel(
		HitResults,
		NextPosition,
		NextPosition,
		GetActorQuat(),
		ECollisionChannel::ECC_Visibility,
		FCollisionShape::MakeCapsule(Radius, HalfHeight),
		CollisionParams
	);

	// 디버그 캡슐 그리기
	//DrawDebugCapsule(
	//	GetWorld(),
	//	NextPosition,                // 캡슐의 중심 위치
	//	HalfHeight,                  // 캡슐의 절반 높이
	//	Radius,                      // 캡슐의 반지름
	//	GetActorQuat(),              // 캡슐의 회전
	//	FColor::Red,                 // 캡슐 색상
	//	false,                       // 지속 시간 여부
	//	1.0f,                        // 지속 시간
	//	0,                           // 깊이 우선 순위
	//	1.0f                         // 선 두께
	//);

	for (FHitResult HitResult : HitResults) {
		FVector ImpactNormal = HitResult.ImpactNormal;
		float DotProduct = FVector::DotProduct(Velocity, ImpactNormal);

		if (DotProduct < 0)
		{
			// 속도를 충돌 표면에 평행한 방향으로 조정
			Velocity -= DotProduct * ImpactNormal;
		}
		
		if (FMath::IsNearlyEqual(FVector::DotProduct(FVector(0, 0, -1), HitResult.ImpactNormal), -1.0f, 0.1f))
		{
			bIsGround = true;
			if (Velocity.Z < 0)Velocity.Z = 0;
		}
	}

	// 다음 위치에 아무것도 충돌하지 않으면 공중에 떠있는 것으로 간주
	if (!bHit) {
		bIsGround = false;
	}
}

void APlayable::UpdatePosition(float DeltaTime)
{
	if (Velocity.IsNearlyZero()) return;
	AddActorWorldOffset(Velocity * DeltaTime);
}