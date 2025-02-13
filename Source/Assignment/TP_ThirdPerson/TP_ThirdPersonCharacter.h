// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "TP_ThirdPersonCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
class UWidgetComponent;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float);

UCLASS(config=Game)
class ATP_ThirdPersonCharacter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* EscAction;

public:
	ATP_ThirdPersonCharacter();
	
private:
	UPROPERTY(EditAnywhere);
	int32 Health;
	UPROPERTY(EditAnywhere);
	int32 MaxHealth;
	UPROPERTY(EditAnywhere)
	UUserWidget* BlindEffectWidget;
	UPROPERTY(EditAnywhere)
	UWidgetComponent* OverheadWidget;

	float OriginalSpeed;
	bool bIsBlinded;
	bool bIsControlReversed;

	FTimerHandle SlowEffectTimerHandle;
	FTimerHandle BlindEffectTimerHandle;
	FTimerHandle ReverseControlEffectTimerHandle;

	void RestoreOriginalSpeed();
	void EndBlindEffect();
	void EndReverseControlEffect();

protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void BeginPlay() override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void ShowMenu(const FInputActionValue& Value);

public:
	FOnHealthChanged OnHealthChanged;

	void AddHealth(int32 Value);
	void ApplyBlind(float Duration);
	void ApplySlow(float SlowAmount, float Duration);
	void ApplyReverseControl(float Duration);

	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	FORCEINLINE int32 GetHealth() const { return Health; }
	FORCEINLINE int32 GetMaxHealth() const { return MaxHealth; }
};

