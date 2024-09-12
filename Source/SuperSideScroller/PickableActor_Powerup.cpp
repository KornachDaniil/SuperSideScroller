// Fill out your copyright notice in the Description page of Project Settings.


#include "PickableActor_Powerup.h"

void APickableActor_Powerup::BeginPlay()
{
	Super::BeginPlay();
	
}

void APickableActor_Powerup::PlayerPickedUp(ASuperSidescroller_Player* Player)
{
	Super::PlayerPickedUp(Player);

	Player->IncreaseMovementPowerup();
}
