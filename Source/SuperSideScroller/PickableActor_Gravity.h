// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickableActor_Base.h"
// ReSharper disable once CppUESourceFileWithoutPredefinedMacros
#include "PickableActor_Gravity.generated.h"

/**
 * 
 */
UCLASS()
class SUPERSIDESCROLLER_API APickableActor_Gravity : public APickableActor_Base
{
	GENERATED_BODY()

public:

protected:
	virtual void BeginPlay() override;

	virtual void PlayerPickedUp(ASuperSidescroller_Player* Player) override;

	
private:

	
};
