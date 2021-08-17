// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "NetPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class NETCONTENT_API ANetPlayerController : public APlayerController
{
	GENERATED_BODY()

	UFUNCTION(Server, Unreliable, BlueprintCallable)
	void PressTheButton();
	void PressTheButton_Implementation();

	UFUNCTION(Client, Unreliable)
	void ReturnToClient();
	void ReturnToClient_Implementation();

public:
	UPROPERTY(BlueprintReadWrite)
	float _lastCallTime;
};
