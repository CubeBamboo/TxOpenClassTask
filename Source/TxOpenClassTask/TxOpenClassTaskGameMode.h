// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Engine/Engine.h"
#include "Kismet/GameplayStatics.h"
#include "TxOpenClassTaskGameMode.generated.h"

UCLASS(minimalapi)
class ATxOpenClassTaskGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ATxOpenClassTaskGameMode();

	void BeginPlay() override
	{
		TArray<AActor*> Actors;
		UGameplayStatics::GetAllActorsWithTag(GetWorld(), "HitBox", Actors);
		
		UE_LOG(LogTemp, Warning, TEXT("GameMode begin play: %d"), Actors.Num());
		for (AActor* Actor : Actors)
		{
			UE_LOG(LogTemp, Warning, TEXT("Actor Name: %s"), *Actor->GetName());
		}
	}
};



