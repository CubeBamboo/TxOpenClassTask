// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Engine/Engine.h"
#include "Kismet/GameplayStatics.h"
#include "TxOpenClassTaskCharacter.h"
#include "TxOpenClassTaskGameMode.generated.h"

UCLASS(minimalapi)
class ATxOpenClassTaskGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ATxOpenClassTaskGameMode();

private:
	UPROPERTY(EditAnywhere, Category = "Gameplay")
	float TimeLimit = 10.0f;

	float currentTime = 0.0f;

public:
	void BeginPlay() override
	{
		Super::BeginPlay();
		//UE_LOG(LogTemp, Warning, TEXT("Game mode begin play!"));
	}

	/*void Tick(float DeltaTime) override
	{
		Super::Tick(DeltaTime);

		UE_LOG(LogTemp, Warning, TEXT("Game mode tick!"));
		currentTime += DeltaTime;
		GEngine->AddOnScreenDebugMessage(0, 2.0f, FColor::Yellow, FString::Printf(TEXT("current time: %d"), currentTime));
		if (currentTime > TimeLimit)
		{
			TArray<AActor*> actors;
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATxOpenClassTaskCharacter::StaticClass(), actors);
			ATxOpenClassTaskCharacter* character = Cast<ATxOpenClassTaskCharacter>(actors[0]);
			auto score = character->GetScore();
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, FString::Printf(TEXT("game end! your score is: %d"), score));
		}
	}*/
};



