// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameMode.h"
#include "Playable.h"
#include "DefaultPlayable.h"
#include "AircraftPlayable.h"
#include "PlayableController.h"

AMyGameMode::AMyGameMode()
{
	PlayerControllerClass = APlayableController::StaticClass();
}
