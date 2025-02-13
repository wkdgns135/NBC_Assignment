// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSlowing.h"
#include "../TP_ThirdPerson/TP_ThirdPersonCharacter.h"

void AItemSlowing::ActivateItem(AActor* Activator)
{
    Super::ActivateItem(Activator);

    if (Activator && Activator->ActorHasTag("Player"))
    {
        Cast<ATP_ThirdPersonCharacter>(Activator)->ApplySlow(0.5, 5);
        Deactivate();
    }
}
