#include "ProgressionComponent.h"

#include "HealthComponent.h"
#include "GameFramework/Actor.h"

UProgressionComponent::UProgressionComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	XPPerLevel = 100;
	MaxHealthUpgradeCost = 50;
	Currency = 0;
	Experience = 0;
	Level = 1;
}

void UProgressionComponent::AddCurrency(int32 Amount)
{
	Currency += Amount;
}

void UProgressionComponent::AddExperience(int32 Amount)
{
	if (Amount <= 0)
	{
		return;
	}

	Experience += Amount;
	while (Experience >= XPPerLevel)
	{
		Experience -= XPPerLevel;
		Level++;
	}
}

bool UProgressionComponent::TryPurchaseMaxHealthUpgrade()
{
	if (Currency < MaxHealthUpgradeCost || !CachedHealth)
	{
		return false;
	}

	Currency -= MaxHealthUpgradeCost;
	const float NewMax = CachedHealth->GetMaxHealth() + 25.f;
	CachedHealth->SetMaxHealth(NewMax);
	return true;
}

void UProgressionComponent::BeginPlay()
{
	Super::BeginPlay();

	if (AActor* Owner = GetOwner())
	{
		CachedHealth = Owner->FindComponentByClass<UHealthComponent>();
	}
}
