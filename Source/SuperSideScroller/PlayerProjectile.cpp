// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerProjectile.h"

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
	

}

void APlayerProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("HIT"));
}

