// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Clickable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UClickable : public UInterface
{
	GENERATED_BODY()
};

/**
 * This interface represent every actor that can be clicked
 */
class NETCONTENT_API IClickable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	/**
	 * Called when an actor is clicked.
	 */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Clickable")
	void ReceiveClick();
	virtual void ReceiveClick_Implementation();
};
