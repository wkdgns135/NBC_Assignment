// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemHpPotion.h"
#include "../TP_ThirdPerson/TP_ThirdPersonCharacter.h"

void AItemHpPotion::ActivateItem(AActor* Activator)
{
    Super::ActivateItem(Activator);

    if (Activator && Activator->ActorHasTag("Player"))
    {
        Cast<ATP_ThirdPersonCharacter>(Activator)->AddHealth(20);
        Deactivate();
    }
}
