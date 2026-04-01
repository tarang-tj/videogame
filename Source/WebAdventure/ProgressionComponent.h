#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ProgressionComponent.generated.h"

class UHealthComponent;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class WEBADVENTURE_API UProgressionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UProgressionComponent();

	UFUNCTION(BlueprintCallable, Category = "Progression")
	void AddCurrency(int32 Amount);

	UFUNCTION(BlueprintCallable, Category = "Progression")
	void AddExperience(int32 Amount);

	/** Spend currency to increase max health (simple upgrade loop) */
	UFUNCTION(BlueprintCallable, Category = "Progression")
	bool TryPurchaseMaxHealthUpgrade();

	UFUNCTION(BlueprintPure, Category = "Progression")
	int32 GetCurrency() const { return Currency; }

	UFUNCTION(BlueprintPure, Category = "Progression")
	int32 GetExperience() const { return Experience; }

	UFUNCTION(BlueprintPure, Category = "Progression")
	int32 GetLevel() const { return Level; }

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Progression")
	int32 XPPerLevel;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Progression")
	int32 MaxHealthUpgradeCost;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Progression")
	int32 Currency;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Progression")
	int32 Experience;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Progression")
	int32 Level;

	UPROPERTY()
	UHealthComponent* CachedHealth;
};
