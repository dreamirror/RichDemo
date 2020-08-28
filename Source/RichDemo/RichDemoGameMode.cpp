// Copyright Epic Games, Inc. All Rights Reserved.

#include "RichDemoGameMode.h"
#include "RichDemoHUD.h"
#include "RichDemoCharacter.h"
#include "UObject/ConstructorHelpers.h"

ARichDemoGameMode::ARichDemoGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ARichDemoHUD::StaticClass();
}
