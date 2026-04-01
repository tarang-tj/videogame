#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyCharacter.generated.h"

class UHealthComponent;

UCLASS()
class WEBADVENTURE_API AEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AEnemyCharacter();

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void ApplyDamage(float DamageAmount);

	UFUNCTION(BlueprintPure, Category = "Combat")
	bool IsDead() const;

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void HandleDeath();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UHealthComponent* HealthComponent;
};
