#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "DoorActor.generated.h"

class UStaticMeshComponent;
class APlayerCharacter;

UCLASS()
class WEBADVENTURE_API ADoorActor : public AActor, public IInteractable
{
	GENERATED_BODY()

public:
	ADoorActor();

	virtual void Interact_Implementation(APlayerCharacter* Instigator) override;
	virtual bool CanInteract_Implementation(APlayerCharacter* Instigator) const override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* DoorMesh;

	/** Opens when player has at least this many collectibles */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door")
	int32 RequiredCollectibles;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Door")
	bool bIsOpen;

	/** Local offset when open (relative) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door")
	FVector OpenOffset;
};
