// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerProjectile.h"

#include "EnemyBase.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
APlayerProjectile::APlayerProjectile()
{
 	CollisiobComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisiobComp->BodyInstance.SetCollisionProfileName("BlockAll");
	CollisiobComp->OnComponentHit.AddDynamic(this, &APlayerProjectile::OnHit);

	RootComponent = CollisiobComp;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisiobComp;
	ProjectileMovement->ProjectileGravityScale = 0.0f;
	ProjectileMovement->InitialSpeed = 1200.0f;
	ProjectileMovement->MaxSpeed = 1200.0f;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);

	InitialLifeSpan = 3.0f;

	ProjectileMovementSound = CreateDefaultSubobject<UAudioComponent>(TEXT("ProjectileMovementSound"));
	ProjectileMovementSound->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);

	ProjectileEffects = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ProjectileEffects"));
	ProjectileEffects->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);

}

void APlayerProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	AEnemyBase* Enemy = Cast<AEnemyBase>(OtherActor);
	if (Enemy != nullptr)
	{
		Enemy->DestroyEnemy();
	}
	ExplodeProjectile();
}

void APlayerProjectile::ExplodeProjectile()
{
	UWorld* World = GetWorld();
	
	if (World != nullptr)
	{
		if (DestroyEffects != nullptr)
		{
			UGameplayStatics::SpawnEmitterAtLocation(World, DestroyEffects, GetActorTransform());
		}
		
		if (DestroySound != nullptr)
		{
			UGameplayStatics::SpawnSoundAtLocation(World, DestroySound, GetActorLocation());
		}
		
		Destroy();
	}
}

