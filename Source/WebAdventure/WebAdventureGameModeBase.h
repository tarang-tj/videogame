#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "WebAdventureGameModeBase.generated.h"

UCLASS()
class WEBADVENTURE_API AWebAdventureGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AWebAdventureGameModeBase();
};

ntureGameModeBase();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Player")
	TSubclassOf<APlayerCharacter> PlayerCharacterClass;
};

