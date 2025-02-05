// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SMChamferCube.generated.h"

UCLASS()
class TXOPENCLASSTASK_API ASMChamferCube : public AActor
{
	GENERATED_BODY()
	
public:	
	int HitCount = 0;
	bool bIsSpecial = false;

	// Sets default values for this actor's properties
	ASMChamferCube();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
