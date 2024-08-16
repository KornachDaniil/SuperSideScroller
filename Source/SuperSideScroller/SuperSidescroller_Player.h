// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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

protected:

	// Существует в базовом классе 
	// UPROPERTY(EditAnywhere, Category="Input")
	// UInputMappingContext* IC_Character;

	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* IA_Sprint;
	
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* IA_Throw;
	
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	void Sprint();
	void StopSprinting();

	void ThrowProjectile();
	
private:
	bool bIsSprinting;
};
