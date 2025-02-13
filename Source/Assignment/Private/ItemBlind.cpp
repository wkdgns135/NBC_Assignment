// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemBlind.h"
#include "../TP_ThirdPerson/TP_ThirdPersonCharacter.h"

void AItemBlind::ActivateItem(AActor* Activator)
{
    Super::ActivateItem(Activator);

    if (Activator && Activator->ActorHasTag("Player"))
    {
        Cast<ATP_ThirdPersonCharacter>(Activator)->ApplyBlind(5);
        Deactivate();
    }
}
