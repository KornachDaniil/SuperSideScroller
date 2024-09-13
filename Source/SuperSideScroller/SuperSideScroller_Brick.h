// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SuperSidescroller_Player.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "SuperSideScroller_Brick.generated.h"

UCLASS()
class SUPERSIDESCROLLER_API ASuperSideScroller_Brick : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASuperSideScroller_Brick();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Brick)
	USoundBase* HitSound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Brick)
	UParticleSystem* Explosion;
	
private:	
	UPROPERTY(VisibleDefaultsOnly, Category=Brick)
	UStaticMeshComponent* BrickMesh;

	UPROPERTY(VisibleDefaultsOnly, Category=Brick)
	UBoxComponent* BrickCollision;

	UPROPERTY(EditAnywhere)
	bool bHasCollectable;

	UPROPERTY(EditAnywhere)
	int32 CollectableValue = 1;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		FVector NormalImpulse, const FHitResult& Hit);

	void AddCollectable(ASuperSidescroller_Player* Player);

	void PlayHitSound();

	void PlayHitExplosion();
};
