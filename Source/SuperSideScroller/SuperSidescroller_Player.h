// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerProjectile.h"
#include "SuperSideScrollerCharacter.h"
#include "SuperSidescroller_Player.generated.h"

/**
 * 
 */
UCLASS()
class SUPERSIDESCROLLER_API ASuperSidescroller_Player : public ASuperSideScrollerCharacter
{
	GENERATED_BODY()

public:
	ASuperSidescroller_Player();

	UFUNCTION(BlueprintPure)
	FORCEINLINE int32 GetCurrentNumberofCollectables() const { return NumberofCollectables; }

	FORCEINLINE bool GetbHasPowerupActive() const { return bHasPowerupActive; }

	UFUNCTION()
	void DeathPlayer();

	void IncrementNumberofCollectables(int32 Value);

	void SpawnProjectile();

	void IncreaseMovementPowerup();

	void EndPowerup();

	void IncreaseMovementGravity();

	void EndGravity();

	UPROPERTY(EditAnywhere, Category=Setup)
	float WalkSpeed;

	UPROPERTY(EditAnywhere, Category=Setup)
	float SprintSpeed;

	UPROPERTY(EditAnywhere, Category=Death)
	USoundBase* DeathSound;

	UPROPERTY(EditAnywhere, Category=Death)
	UParticleSystem* DeathEffect;

protected:
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* IA_Sprint;
	
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* IA_Throw;

	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* IA_Quit;
	
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	void Sprint();
	void StopSprinting();

	void ThrowProjectile();

	void QuitGame();
	
private:
	UPROPERTY(EditAnywhere)
	UAnimMontage* ThrowMontage;

	UPROPERTY(EditAnywhere)
	TSubclassOf<APlayerProjectile> PlayerProjectile;
	
	int32 NumberofCollectables;

	FTimerHandle PowerupHandle;

	FTimerHandle GravityHandle;
	
	bool bIsSprinting;
	
	bool bHasPowerupActive;

	bool bHasGravityActive;
};
