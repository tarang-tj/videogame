#include "EnemyCharacter.h"

#include "HealthComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

AEnemyCharacter::AEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	GetCharacterMovement()->MaxWalkSpeed = 300.f;

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
}

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (HealthComponent)
	{
		HealthComponent->OnDeath.AddDynamic(this, &AEnemyCharacter::HandleDeath);
	}
}

void AEnemyCharacter::ApplyDamage(float DamageAmount)
{
	if (HealthComponent)
	{
		HealthComponent->ApplyHealthChange(-FMath::Abs(DamageAmount));
	}
}

bool AEnemyCharacter::IsDead() const
{
	return HealthComponent ? HealthComponent->IsDead() : true;
}

void AEnemyCharacter::HandleDeath()
{
	Destroy();
}
