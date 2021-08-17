// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "OnlineButton.generated.h"

UCLASS()
class NETCONTENT_API AOnlineButton : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AOnlineButton();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(Server, Unreliable, BlueprintCallable)
	void PressTheButton();
	void PressTheButton_Implementation();

	UFUNCTION(Client, Unreliable)
	void ReturnToClient();
	void ReturnToClient_Implementation();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
