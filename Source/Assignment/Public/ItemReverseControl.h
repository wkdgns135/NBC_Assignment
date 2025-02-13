// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"
#include "ItemReverseControl.generated.h"

/**
 * 
 */
UCLASS()
class ASSIGNMENT_API AItemReverseControl : public ABaseItem
{
	GENERATED_BODY()
	
public:
	virtual void ActivateItem(AActor* Activator) override;
};
