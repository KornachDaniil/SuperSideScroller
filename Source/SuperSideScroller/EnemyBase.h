// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SuperSideScrollerCharacter.h"
#include "Components/SphereComponent.h"
#include "EnemyBase.generated.h"

/**
 * 
 */
UCLASS()
class SUPERSIDESCROLLER_API AEnemyBase : public ASuperSideScrollerCharacter
{
	GENERATED_BODY()

public:
	AEnemyBase();
	
	void DestroyEnemy();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UParticleSystem* DeathEffect;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USoundBase* DeathSound;

	UPROPERTY(VisibleDefaultsOnly)
	USphereComponent* CollisionComp;

	UFUNCTION()
	void OnOverlap(class UPrimitiveComponent* ThisComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	
protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float WalkSpeed = 500.0f;

	void RespawnPlayer() const;

	FTimerHandle PlayerRespawnHandle;

private:
};
