#include "HealthComponent.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	MaxHealth = 100.f;
	Health = MaxHealth;
	bIsDead = false;
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;
	bIsDead = false;
	OnHealthChanged.Broadcast(Health, 0.f);
}

void UHealthComponent::ApplyHealthChange(float Delta)
{
	if (bIsDead || Delta == 0.f)
	{
		return;
	}

	const float OldHealth = Health;
	Health = FMath::Clamp(Health + Delta, 0.f, MaxHealth);
	const float ActualDelta = Health - OldHealth;

	if (!FMath::IsNearlyZero(ActualDelta))
	{
		OnHealthChanged.Broadcast(Health, ActualDelta);
	}

	if (!bIsDead && Health <= 0.f)
	{
		bIsDead = true;
		OnDeath.Broadcast();
	}
}

void UHealthComponent::SetMaxHealth(float NewMaxHealth)
{
	MaxHealth = FMath::Max(1.f, NewMaxHealth);
	Health = FMath::Min(Health, MaxHealth);
	OnHealthChanged.Broadcast(Health, 0.f);
}

