// Fill out your copyright notice in the Description page of Project Settings.


#include "DisappearActor.h"

// Sets default values
ADisappearActor::ADisappearActor()
{
	PrimaryActorTick.bCanEverTick = false;
	DisappearTime = 5.0f;
}

// Called when the game starts or when spawned
void ADisappearActor::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ADisappearActor::Disappear, DisappearTime);
}

// Called every frame
void ADisappearActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADisappearActor::Disappear()
{
	Destroy();
}

