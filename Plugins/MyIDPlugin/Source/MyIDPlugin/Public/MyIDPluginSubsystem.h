// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "MyIDPluginSubsystem.generated.h"

UCLASS()
class UMyIDPluginSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

private:
	FString UserName;
	
public:
	UFUNCTION(BlueprintCallable, Category = "MyIDPlugin")
	FORCEINLINE void SetUserName(const FString& NewName){UserName = NewName;}
	UFUNCTION(BlueprintCallable, Category = "MyIDPlugin")
	FORCEINLINE FString GetUserName() const {return UserName;}
};
