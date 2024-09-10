// Fill out your copyright notice in the Description page of Project Settings.


#include "PickableActor_Base.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
APickableActor_Base::APickableActor_Base()
{
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComp"));
	CollisionComp->InitSphereRadius(30.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("OverlapAllDynamic");

	RootComponent = CollisionComp;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	RotationComp = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("RotationComp"));

	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &APickableActor_Base::BeginOverlap);
	
}

// Called when the game starts or when spawned
void APickableActor_Base::BeginPlay()
{
	Super::BeginPlay();
	
}

void APickableActor_Base::BeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ASuperSidescroller_Player* Player = Cast<ASuperSidescroller_Player>(OtherActor);

	if (Player != nullptr)
	{
		PlayerPickedUp(Player);	
	}
}

void APickableActor_Base::PlayerPickedUp(ASuperSidescroller_Player* Player)
{
	UWorld* World = GetWorld();

	if (World != nullptr)
	{
		if (PickupSound != nullptr)
		{
			UGameplayStatics::PlaySoundAtLocation(World, PickupSound, GetActorLocation());
		}
		
		Destroy();
	}
}
