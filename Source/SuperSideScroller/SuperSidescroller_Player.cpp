// Fill out your copyright notice in the Description page of Project Settings.


#include "SuperSidescroller_Player.h"

#include "EnemyBase.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

ASuperSidescroller_Player::ASuperSidescroller_Player()
{
	bIsSprinting = false;

	bCanFire = false;

	IA_Sprint = nullptr;

	WalkSpeed = 300.0f;

	SprintSpeed = 500.0f;

	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
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
		if (bHasPowerupActive == true)
		{
			GetCharacterMovement()->MaxWalkSpeed = 900.0f;
		}
		else
		{
			GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
		}
	}
}

void ASuperSidescroller_Player::StopSprinting()
{
	if (bIsSprinting != false)
	{
		bIsSprinting = false;
		if (bHasPowerupActive == true)
		{
			GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
		}
		else
		{
			GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
		}
	}
}

void ASuperSidescroller_Player::ThrowProjectile()
{
	
	if (ThrowMontage != nullptr && GetActorForwardVector().X < 0.1f)
	{
		bCanFire = true;
		const bool bIsMontagePlaying = GetMesh()->GetAnimInstance()->Montage_IsPlaying(ThrowMontage);
		if(bIsMontagePlaying != true)
		{
			GetMesh()->GetAnimInstance()->Montage_Play(ThrowMontage, 2.0f);
		}
	}
}

void ASuperSidescroller_Player::IncrementNumberofCollectables(int32 Value)
{
	if (Value <= 0)
	{
		return;
	}
	else
	{
		NumberofCollectables += Value;

		if (NumberofCollectables == 10)
		{
			WalkSpeed = 400.0f;
			SprintSpeed = 600.0f;
			
			if (bIsSprinting == true)
			{
				GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
			}
			else
			{
				GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
			}
		}
		if (NumberofCollectables == 21)
		{
			UKismetSystemLibrary::QuitGame(GetWorld(), 0, EQuitPreference::Quit, false);
		}
	}
}

void ASuperSidescroller_Player::SpawnProjectile()
{
	if (PlayerProjectile != nullptr && bCanFire == true)
	{
		UWorld* World = GetWorld();
		if (World != nullptr)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			const FVector SpawnLocation = this->GetMesh()->GetSocketLocation(FName("ProjectileSocket"));
			const FRotator Rotation = GetActorForwardVector().Rotation();
			World->SpawnActor<APlayerProjectile>(PlayerProjectile, SpawnLocation, Rotation, SpawnParams);
		}
		bCanFire = false;
	}
}

void ASuperSidescroller_Player::IncreaseMovementPowerup()
{
	bHasPowerupActive = true;
	
	if (bIsSprinting == true)
	{
		GetCharacterMovement()->MaxWalkSpeed = 900.0f;
	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
	}
	
	GetCharacterMovement()->JumpZVelocity = 1500.0f;

	UWorld* World = GetWorld();

	if (World != nullptr)
	{
		World->GetTimerManager().SetTimer(PowerupHandle, this, &ASuperSidescroller_Player::EndPowerup, 8.0f, false);
	}
}

void ASuperSidescroller_Player::EndPowerup()
{
	bHasPowerupActive = false;
	if (bIsSprinting == false)
	{
		GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
	}
	
	GetCharacterMovement()->JumpZVelocity = 1000.0f;

	UWorld* World = GetWorld();

	if (World != nullptr)
	{
		World->GetTimerManager().ClearTimer(PowerupHandle);
	}
}

void ASuperSidescroller_Player::IncreaseMovementGravity()
{
	bHasGravityActive = true;

	GetCharacterMovement()->GravityScale = 1.0f;

	UWorld* World = GetWorld();

	if (World != nullptr)
	{
		World->GetTimerManager().SetTimer(GravityHandle, this, &ASuperSidescroller_Player::EndGravity, 8.0f, false);
	}
}

void ASuperSidescroller_Player::EndGravity()
{
	bHasGravityActive = false;

	GetCharacterMovement()->GravityScale = 2.0f;

	UWorld* World = GetWorld();

	if (World != nullptr)
	{
		World->GetTimerManager().ClearTimer(GravityHandle);
	}
}

void ASuperSidescroller_Player::DeathPlayer()
{
	UWorld* World = GetWorld();

	if (World != nullptr)
	{
		if (DeathSound != nullptr)
		{
			UGameplayStatics::SpawnSoundAtLocation(World, DeathSound, GetActorLocation());
		}
		if (DeathEffect != nullptr)
		{
			UGameplayStatics::SpawnEmitterAtLocation(World, DeathEffect, GetActorTransform());
		}
		Destroy();
	}
}