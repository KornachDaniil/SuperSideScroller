// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "PlayerProjectile.generated.h"

UCLASS()
class SUPERSIDESCROLLER_API APlayerProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlayerProjectile();

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector 
	  NormalImpulse, const FHitResult& Hit);

	void ExplodeProjectile();
	
	UPROPERTY(VisibleDefaultsOnly, Category=Projectile)
	USphereComponent* CollisiobComp;
	
protected:


private:	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Movement, meta=(AllowPrivateAccess = "true"))
	UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(EditAnywhere, Category=Projectile)
	UStaticMeshComponent* MeshComp;

	UPROPERTY(VisibleDefaultsOnly, Category=Sound)
	UAudioComponent* ProjectileMovementSound;

	UPROPERTY(VisibleDefaultsOnly, Category=Projectile)
	UParticleSystemComponent* ProjectileEffects;

	UPROPERTY(EditAnywhere, Category=Sound)
	USoundBase* DestroySound;

	UPROPERTY(EditAnywhere, Category=Projectile)
	UParticleSystem* DestroyEffects;
	
};
