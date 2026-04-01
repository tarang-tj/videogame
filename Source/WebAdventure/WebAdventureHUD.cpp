#include "WebAdventureHUD.h"

#include "Blueprint/UserWidget.h"
#include "Engine/Engine.h"

void AWebAdventureHUD::BeginPlay()
{
	Super::BeginPlay();

	if (!HUDWidgetClass)
	{
		return;
	}

	APlayerController* PC = GetOwningPlayerController();
	if (!PC)
	{
		return;
	}

	HUDWidget = CreateWidget<UUserWidget>(PC, HUDWidgetClass);
	if (HUDWidget)
	{
		HUDWidget->AddToViewport();
	}
}
