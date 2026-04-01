#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Collectible.generated.h"

class USphereComponent;
class UStaticMeshComponent;

UCLASS()
class WEBADVENTURE_API ACollectible : public AActor
{
	GENERATED_BODY()

public:
	ACollectible();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USphereComponent* CollisionSphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* Mesh;

	/** How many “fragments” this pickup grants */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collectible")
	int32 Value;
};
