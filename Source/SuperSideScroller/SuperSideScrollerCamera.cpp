// Fill out your copyright notice in the Description page of Project Settings.


#include "SuperSideScrollerCamera.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ASuperSideScrollerCamera::ASuperSideScrollerCamera()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller
    
	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
	
}

// Called when the game starts or when spawned
void ASuperSideScrollerCamera::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASuperSideScrollerCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

FVector ASuperSideScrollerCamera::CalculateCameraPosition(ACharacter* Player)
{
	UWorld* World = GetWorld();
	FVector NewLocation;
	if (World != nullptr)
	{
		FVector Target = Player->GetActorLocation();
		NewLocation = FMath::VInterpTo(GetActorLocation(), Target, World->GetDeltaSeconds(), 5.0f);
	}
	return NewLocation;
}

