#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UHealthComponent;
class UProgressionComponent;

UCLASS()
class WEBADVENTURE_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "Game")
	void AddCollectibles(int32 Amount);

	UFUNCTION(BlueprintPure, Category = "Game")
	int32 GetCollectibleCount() const { return CollectibleCount; }

protected:
	virtual void BeginPlay() override;

	/** Movement input handlers */
	void MoveForward(float Value);
	void MoveRight(float Value);

	/** Look input handlers */
	void LookUp(float Value);
	void Turn(float Value);

	/** Action handlers */
	void StartJump();
	void StopJump();
	void StartSprint();
	void StopSprint();

	void TryInteract();
	void TryAttack();

protected:
	/** Third-person camera boom */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	UCameraComponent* FollowCamera;

	/** Health component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UHealthComponent* HealthComponent;

	/** Currency, XP, upgrades */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UProgressionComponent* ProgressionComponent;

	/** Walk and sprint speeds */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
	float WalkSpeed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
	float SprintSpeed;

	/** Whether the character is currently sprinting */
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Movement")
	bool bIsSprinting;

	/** Collected pickups (gates doors, objectives) */
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Game")
	int32 CollectibleCount;

	/** Melee ray damage */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat")
	float MeleeDamage;

	/** Interact / attack trace length */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat")
	float InteractionRange;
};

