// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AssignmentPlayerController.generated.h"

class UGameWidget;
/**
 * 
 */
UCLASS()
class ASSIGNMENT_API AAssignmentPlayerController : public APlayerController
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category = "Widget")
	UGameWidget* GameWidget;
	
public:
	virtual void BeginPlay() override;
	UFUNCTION(Client, Unreliable)
	void ClientUpdateOtherPlayerNum(const FString& PlayerNumString);

private:
	UFUNCTION(Server, Unreliable)
	void ServerUpdatePlayerNum(const FString& PlayerNumString);
};
