// Copyright Epic Games, Inc. All Rights Reserved.

#include "TxOpenClassTaskProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "TP_WeaponComponent.h"
#include "TxOpenClassTaskCharacter.h"
#include "SMChamferCube.h"

#define MScreenMsg(t) GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, t)

ATxOpenClassTaskProjectile::ATxOpenClassTaskProjectile() 
{
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &ATxOpenClassTaskProjectile::OnHit);		// set up a notification for when this component hits something blocking

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = CollisionComp;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;
}

void ATxOpenClassTaskProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString("Hit on!"));
		//auto log = FString::Printf(TEXT("actor: %s"), *OtherActor->GetName());
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, log);

		auto cube = Cast<ASMChamferCube>(OtherActor);
		if (!cube)
		{
			UE_LOG(LogTemp, Warning, TEXT("not a cube"));
			return;
		}

		OnHitDelegate.Broadcast(HitComp, OtherActor, OtherComp, NormalImpulse, Hit);
		cube->hitCount++;

		if (cube->hitCount == 1)
		{
			// random scale
			OtherActor->SetActorRelativeScale3D(FVector(FMath::RandRange(1, 4), FMath::RandRange(1, 4), FMath::RandRange(1, 4)));
		}
		else
		{
			OtherActor->Destroy();
		}

		// add score
		if (Weapon)
		{
			auto score = cube->isSpecial ? 10 : 5;
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("add score: %d"), score));
			Weapon->GetCharacter()->AddScore(score);
		}

		Destroy();
	}
}
