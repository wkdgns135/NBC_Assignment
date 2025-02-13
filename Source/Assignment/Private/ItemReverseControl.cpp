// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemReverseControl.h"
#include "../TP_ThirdPerson/TP_ThirdPersonCharacter.h"

void AItemReverseControl::ActivateItem(AActor* Activator)
{
    Super::ActivateItem(Activator);

    if (Activator && Activator->ActorHasTag("Player"))
    {
        Cast<ATP_ThirdPersonCharacter>(Activator)->ApplyReverseControl(5);
        Deactivate();
    }
}
