// Copyright Epic Games, Inc. All Rights Reserved.

#include "TxOpenClassTaskGameMode.h"
#include "TxOpenClassTaskCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATxOpenClassTaskGameMode::ATxOpenClassTaskGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
