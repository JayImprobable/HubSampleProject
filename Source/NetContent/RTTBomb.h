// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "Components/TextRenderComponent.h"
#include "RTTBomb.generated.h"

UCLASS()
class NETCONTENT_API ARTTBomb : public AActor, public IInteractable
{
	GENERATED_BODY()

	UPROPERTY(VisibleDefaultsOnly)
	UTextRenderComponent* RTTTextFeedback;

protected:
	UPROPERTY()
	float lastCallTime;

	FTimerHandle timeOutHandle;

	bool running;

	
public:	
	// Sets default values for this actor's properties
	ARTTBomb();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Server RPC
	UFUNCTION(Server, Reliable, BlueprintCallable)
	void CallServer();
	void CallServer_Implementation();

	//Client RPC
	UFUNCTION(Client, Unreliable)
	void ReturnToClient();
	void ReturnToClient_Implementation();

	//Blueprint Event that starts the cosmetic representation
	UFUNCTION(BlueprintNativeEvent)
	void StartExplosionVisual();
	virtual void StartExplosionVisual_Implementation();

	//Blueprint Event that finishes the cosmetic representation
	UFUNCTION(BlueprintNativeEvent)
	void FinishExplosionVisual(float RTT);
	virtual void FinishExplosionVisual_Implementation(float RTT);

	UFUNCTION()
	void RunTimeOut();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Activation_Implementation(AController* controller) override;

	

};
