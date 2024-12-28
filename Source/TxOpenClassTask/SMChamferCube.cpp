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
	isSpecial = FMath::RandRange(0, 10) < 3;
	if (isSpecial)
	{
		auto meshComp = FindComponentByClass<UStaticMeshComponent>();
		UMaterialInstanceDynamic* dynamicMaterialInstance = UMaterialInstanceDynamic::Create(meshComp->GetMaterial(0), this);

		// 设置颜色参数
		FLinearColor NewColor(1.0f, 0.0f, 0.0f, 1.0f); // 红色
		dynamicMaterialInstance->SetVectorParameterValue("Base Color", NewColor);

		// 将动态材质实例应用到组件
		meshComp->SetMaterial(0, dynamicMaterialInstance);
	}
}

// Called every frame
void ASMChamferCube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

