// Fill out your copyright notice in the Description page of Project Settings.


#include "Anim_ProjectileNotify.h"

#include "SuperSidescroller_Player.h"

void UAnim_ProjectileNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                    const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	ASuperSidescroller_Player* Player = Cast<ASuperSidescroller_Player>(MeshComp->GetOwner());
	if (Player != nullptr)
	{
		Player->SpawnProjectile();
	}
}
