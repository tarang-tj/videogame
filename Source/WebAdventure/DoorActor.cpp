#include "DoorActor.h"

#include "Components/StaticMeshComponent.h"
#include "PlayerCharacter.h"

ADoorActor::ADoorActor()
{
	PrimaryActorTick.bCanEverTick = false;

	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	RootComponent = DoorMesh;

	RequiredCollectibles = 3;
	bIsOpen = false;
	OpenOffset = FVector(0.f, 0.f, 120.f);
}

void ADoorActor::Interact_Implementation(APlayerCharacter* Instigator)
{
	if (!Instigator || bIsOpen)
	{
		return;
	}

	if (Instigator->GetCollectibleCount() < RequiredCollectibles)
	{
		return;
	}

	bIsOpen = true;
	AddActorLocalOffset(OpenOffset);
}

bool ADoorActor::CanInteract_Implementation(APlayerCharacter* Instigator) const
{
	if (!Instigator || bIsOpen)
	{
		return false;
	}
	return Instigator->GetCollectibleCount() >= RequiredCollectibles;
}
