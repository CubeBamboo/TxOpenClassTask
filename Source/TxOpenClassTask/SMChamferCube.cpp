// Fill out your copyright notice in the Description page of Project Settings.

#include "SMChamferCube.h"

// Sets default values
ASMChamferCube::ASMChamferCube()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASMChamferCube::BeginPlay()
{
	Super::BeginPlay();
	
	// random set up the cube to be special
	bIsSpecial = FMath::RandRange(0, 10) < 3;
	if (bIsSpecial)
	{
		auto meshComp = FindComponentByClass<UStaticMeshComponent>();
		UMaterialInstanceDynamic* dynamicMaterialInstance = UMaterialInstanceDynamic::Create(meshComp->GetMaterial(0), this);

		// setup color parameter
		constexpr FLinearColor NewColor(1.0f, 0.0f, 0.0f, 1.0f); // red
		dynamicMaterialInstance->SetVectorParameterValue("Base Color", NewColor);

		// apply material
		meshComp->SetMaterial(0, dynamicMaterialInstance);
	}
}

// Called every frame
void ASMChamferCube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

