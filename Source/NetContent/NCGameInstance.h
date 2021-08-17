// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "NCGameInstance.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSettingChangeDelegate, float, value);

UCLASS()
class NETCONTENT_API UNCGameInstance : public UGameInstance
{
	GENERATED_BODY()

private:
	UPROPERTY()
	float pktLag;

	UPROPERTY()
	float pktLagVariance;

	UPROPERTY()
	float pktLoss;

public: 
	//Delegates to keep all Totem actors and sliders with updated values
	UPROPERTY(BlueprintAssignable)
	FSettingChangeDelegate OnPktLagChange;

	UPROPERTY(BlueprintAssignable)
	FSettingChangeDelegate OnPktLagVarianceChange;

	UPROPERTY(BlueprintAssignable)
	FSettingChangeDelegate OnPktLossChange;


public:
	UFUNCTION(BlueprintCallable)
	float GetPktLag() const;

	UFUNCTION(BlueprintCallable)
	void SetPktLag(float value);

	UFUNCTION(BlueprintCallable)
	float PktLagVariance() const;

	UFUNCTION(BlueprintCallable)
	void SetPktLagVariance(float value);

	UFUNCTION(BlueprintCallable)
	float GetPktLoss() const;

	UFUNCTION(BlueprintCallable)
	void SetPktLoss(float value);

	
};
