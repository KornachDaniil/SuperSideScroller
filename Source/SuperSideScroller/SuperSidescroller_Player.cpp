// Fill out your copyright notice in the Description page of Project Settings.


#include "SuperSidescroller_Player.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"

ASuperSidescroller_Player::ASuperSidescroller_Player()
{
	bIsSprinting = false;

	// IC_Character = nullptr;

	IA_Sprint = nullptr;

	GetCharacterMovement()->MaxWalkSpeed = 300.0f;
}

void ASuperSidescroller_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (EnhancedInputComponent != nullptr)
	{
		APlayerController* PlayerController = Cast<APlayerController>(GetController());

		if (PlayerController != nullptr)
		{
			// Сделано в базовом классе
			// UEnhancedInputLocalPlayerSubsystem* EnhancedSubsystem
			// 	= ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
			//
			// if (EnhancedSubsystem != nullptr)
			// {
			// 	EnhancedSubsystem->AddMappingContext(IC_Character, 1);
			// }
			EnhancedInputComponent->BindAction(IA_Sprint, ETriggerEvent::Triggered, this, &ASuperSidescroller_Player::Sprint);
			EnhancedInputComponent->BindAction(IA_Sprint, ETriggerEvent::Completed, this, &ASuperSidescroller_Player::StopSprinting);
			EnhancedInputComponent->BindAction(IA_Throw, ETriggerEvent::Started, this, &ASuperSidescroller_Player::ThrowProjectile);
		}
	}
}

void ASuperSidescroller_Player::Sprint()
{
	if (bIsSprinting != true)
	{
		bIsSprinting = true;
		GetCharacterMovement()->MaxWalkSpeed = 500.0f;
	}
}

void ASuperSidescroller_Player::StopSprinting()
{
	if (bIsSprinting != false)
	{
		bIsSprinting = false;
		GetCharacterMovement()->MaxWalkSpeed = 300.0f;
	}
}

void ASuperSidescroller_Player::ThrowProjectile()
{
	UE_LOG(LogTemp, Warning, TEXT("Hello World"));
}
