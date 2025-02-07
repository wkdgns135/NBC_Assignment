// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"
#include "ItemCoin.generated.h"

/**
 * 
 */
UCLASS()
class ASSIGNMENT_API AItemCoin : public ABaseItem
{
	GENERATED_BODY()

public:
	virtual void ActivateItem(AActor* Activator) override;

private:
	UPROPERTY(EditAnywhere, Category = "Item")uint32 PointValue;

public:
	FORCEINLINE void SetPointValue(int32 Value) { PointValue = Value; };
};
