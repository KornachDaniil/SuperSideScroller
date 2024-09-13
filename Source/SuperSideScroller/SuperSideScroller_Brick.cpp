// Fill out your copyright notice in the Description page of Project Settings.


#include "SuperSideScroller_Brick.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
ASuperSideScroller_Brick::ASuperSideScroller_Brick()
{
	BrickMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BrickMesh"));
	BrickMesh->SetCollisionProfileName("BlockAll");

	RootComponent = BrickMesh;

	BrickCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BrickCollision"));
	BrickCollision->SetCollisionProfileName("BlockAll");
	BrickCollision->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);

	BrickCollision->OnComponentHit.AddDynamic(this, &ASuperSideScroller_Brick::OnHit);
	
}

// Called when the game starts or when spawned
void ASuperSideScroller_Brick::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASuperSideScroller_Brick::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	ASuperSidescroller_Player* Player = Cast<ASuperSidescroller_Player>(OtherActor);

	if (Player != nullptr)
	{
		if (bHasCollectable == true)
		{
			AddCollectable(Player);
			PlayHitSound();
			PlayHitExplosion();
		}
		Destroy();
	}
}

void ASuperSideScroller_Brick::AddCollectable(ASuperSidescroller_Player* Player)
{
	Player->IncrementNumberofCollectables(CollectableValue);
}

void ASuperSideScroller_Brick::PlayHitSound()
{
	UWorld* World = GetWorld();

	if (World != nullptr)
	{
		if (HitSound != nullptr)
		{
			UGameplayStatics::SpawnSoundAtLocation(World, HitSound, GetActorLocation());
		}
	}
}

void ASuperSideScroller_Brick::PlayHitExplosion()
{
	UWorld* World = GetWorld();

	if (World != nullptr)
	{
		if (Explosion != nullptr)
		{
			UGameplayStatics::SpawnEmitterAtLocation(World, Explosion, GetActorTransform());
		}
	}
}
