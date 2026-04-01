#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interactable.generated.h"

class APlayerCharacter;

UINTERFACE(MinimalAPI, BlueprintType)
class UInteractable : public UInterface
{
	GENERATED_BODY()
};

class WEBADVENTURE_API IInteractable
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interactable")
	void Interact(APlayerCharacter* Instigator);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interactable")
	bool CanInteract(APlayerCharacter* Instigator) const;
};
