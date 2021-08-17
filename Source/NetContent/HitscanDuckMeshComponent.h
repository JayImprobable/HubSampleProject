// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "HitscanDuckMeshComponent.generated.h"

/**
 * 
 */
UCLASS()
class NETCONTENT_API UHitscanDuckMeshComponent : public UStaticMeshComponent
{
	GENERATED_BODY()
	

public: 
	UPROPERTY(BlueprintReadWrite)
	uint8 bIsDown : 1;
};
