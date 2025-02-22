// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SuperSidescroller_Player.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "PickableActor_Base.generated.h"

UCLASS()
class SUPERSIDESCROLLER_API APickableActor_Base : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickableActor_Base();

	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor
		, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	virtual void PlayerPickedUp(ASuperSidescroller_Player* Player);

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USoundBase* PickupSound;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleDefaultsOnly, Category=PickapbleItem)
	USphereComponent* CollisionComp;
	
	UPROPERTY(VisibleDefaultsOnly, Category=PickapbleItem)
	UStaticMeshComponent* MeshComp;

	UPROPERTY(VisibleDefaultsOnly, Category=PickapbleItem)
	URotatingMovementComponent* RotationComp;

	
};
