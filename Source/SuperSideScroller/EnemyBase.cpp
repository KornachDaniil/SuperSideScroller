// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBase.h"

#include "SuperSidescroller_Player.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"


AEnemyBase::AEnemyBase()
{
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComp"));
	CollisionComp->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);

	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &AEnemyBase::OnOverlap);
}


void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();

	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	
}

void AEnemyBase::DestroyEnemy()
{

	UWorld* World = GetWorld();
	
	if (World)
	{
		if (DeathEffect)
		{
			UGameplayStatics::SpawnEmitterAtLocation(World, DeathEffect, GetActorTransform());
		}
		
		if (DeathSound)
		{
			UGameplayStatics::SpawnSoundAtLocation(World, DeathSound, GetActorLocation());	
		}
		
		Destroy();
	}
	
}

void AEnemyBase::OnOverlap(UPrimitiveComponent* ThisComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ASuperSidescroller_Player* Player = Cast<ASuperSidescroller_Player>(OtherActor);

	if (Player != nullptr)
	{
		if (Player->GetbHasPowerupActive() == true)
		{
			DestroyEnemy();
		}
		else
		{
			Player->Destroy();
			UKismetSystemLibrary::QuitGame(GetWorld(), 0, EQuitPreference::Quit, false);
		}
	}
}

