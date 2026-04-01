#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "WebAdventureHUD.generated.h"

class UUserWidget;

UCLASS()
class WEBADVENTURE_API AWebAdventureHUD : public AHUD
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	/** Assign a UMG widget (e.g. WBP_HUD) in Blueprint defaults */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UUserWidget> HUDWidgetClass;

protected:
	UPROPERTY()
	UUserWidget* HUDWidget;
};
