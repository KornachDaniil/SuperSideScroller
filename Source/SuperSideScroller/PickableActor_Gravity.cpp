// Fill out your copyright notice in the Description page of Project Settings.


#include "PickableActor_Gravity.h"

void APickableActor_Gravity::BeginPlay()
{
	Super::BeginPlay();
	
}

void APickableActor_Gravity::PlayerPickedUp(ASuperSidescroller_Player* Player)
{
	Super::PlayerPickedUp(Player);

	Player->IncreaseMovementGravity();
}
