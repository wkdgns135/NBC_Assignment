// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"

// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Start = { 0 ,0 };
}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();
	Pos = Start;
	for (int i = 0; i < 10; i++)Move();
	PrintTotal();
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float AMyActor::Distance(const FVector2D& a, const FVector2D& b)
{
	return sqrt(pow((b.X - a.X), 2) + pow((b.Y - b.X), 2));
}

void AMyActor::Move()
{
	FVector2D PrevPos = Pos;
	Pos = { Pos.X + Step() , Pos.Y + Step() };
	UE_LOG(LogTemp, Display, TEXT("Move Position : (%d, %d), Distance : %f"), (int)Pos.X, (int)Pos.Y, Distance(PrevPos, Pos));

	if (Step()) { // 0 or 1
		EventFunction();
	}
}

uint32 AMyActor::Step()
{
	return FMath::RandRange(0, 1);
}

void AMyActor::EventFunction()
{
	UE_LOG(LogTemp, Display, TEXT("Event Triggered"));
	EventCount++;
}

void AMyActor::PrintTotal()
{
	UE_LOG(LogTemp, Display, TEXT("Total move distance : %f"), Distance(Start, Pos));
	UE_LOG(LogTemp, Display, TEXT("Total event count : %d"), EventCount);
}


