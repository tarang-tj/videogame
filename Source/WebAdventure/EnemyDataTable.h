#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "EnemyDataTable.generated.h"

/** Row type for a DataTable of enemy tuning (spawn in editor: Miscellaneous → Data Table → EnemyStatsRow) */
USTRUCT(BlueprintType)
struct WEBADVENTURE_API FEnemyStatsRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	FName EnemyId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	float MaxHealth = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	float WalkSpeed = 300.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	float MeleeDamage = 15.f;
};
