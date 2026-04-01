#include "WebAdventureGameModeBase.h"
#include "PlayerCharacter.h"
#include "WebAdventureHUD.h"

AWebAdventureGameModeBase::AWebAdventureGameModeBase()
{
	DefaultPawnClass = APlayerCharacter::StaticClass();
	HUDClass = AWebAdventureHUD::StaticClass();
}

