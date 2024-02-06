// Copyright Epic Games, Inc. All Rights Reserved.

#include "GLMPGameMode.h"
#include "GLMPCharacter.h"
#include "UObject/ConstructorHelpers.h"

AGLMPGameMode::AGLMPGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
