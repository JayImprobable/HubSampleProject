// Copyright Epic Games, Inc. All Rights Reserved.

#include "NetContentGameMode.h"
#include "NetContentHUD.h"
#include "NetContentCharacter.h"
#include "UObject/ConstructorHelpers.h"

ANetContentGameMode::ANetContentGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ANetContentHUD::StaticClass();
}

void ANetContentGameMode::SetOwnerToClient(AActor * actor)
{
	ClientActors.Add(actor);
}
