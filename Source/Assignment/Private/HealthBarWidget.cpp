// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthBarWidget.h"
#include "../TP_ThirdPerson/TP_ThirdPersonCharacter.h"

void UHealthBarWidget::NativeConstruct()
{
	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		if (APawn* Pawn = PlayerController->GetPawn())
		{
			Player = Cast<ATP_ThirdPersonCharacter>(Pawn);
			if (Player)
			{
				Player->OnHealthChanged.AddUObject(this, &UHealthBarWidget::OnHealthUpdated);
			}
		}
	}
}

void UHealthBarWidget::OnHealthUpdated(float NewHealth)
{
	if (Player && ProgressBar)
	{
		float HealthPercent = NewHealth / Player->GetMaxHealth();
		ProgressBar->SetPercent(HealthPercent);
	}
}
