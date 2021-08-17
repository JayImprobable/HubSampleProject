// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "NetContentGameMode.generated.h"

UCLASS(minimalapi)
class ANetContentGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly)
	TArray<AActor*> ClientActors;

public:
	ANetContentGameMode();

	UFUNCTION(BlueprintCallable)
	void SetOwnerToClient(AActor* actor);
};



