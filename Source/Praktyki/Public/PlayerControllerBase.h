// Copyright 2023 Teyon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerControllerBase.generated.h"

/**
 * 
 */
UCLASS()
class PRAKTYKI_API APlayerControllerBase : public APlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void SetupInputComponent() override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = Input)
	class UInputMappingContext* InputMappingContext;
};
