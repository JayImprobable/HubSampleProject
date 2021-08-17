// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Shootable.h"
#include "Duck.generated.h"

UCLASS()
class NETCONTENT_API ADuck : public AActor, public IShootable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TimeToReturn;

	//Default system to be spawned on when this actor is activated.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UParticleSystem* LocalFeedbackSystem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = "true"))
	uint8 bClientAuthority:1;

protected: 
	UPROPERTY(ReplicatedUsing=OnRepIsDown)
	uint8 bIsDown:1;


	FTimerHandle handle;

public:	
	// Sets default values for this actor's properties
	ADuck();

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(NetMulticast, Reliable)
	void DistributeShotAmongAllClients();
	void DistributeShotAmongAllClients_Implementation();

	UFUNCTION(NetMulticast, Reliable)
	void ServerResetDuck();
	void ServerResetDuck_Implementation();

	UFUNCTION(Server, Reliable)
	void ServerShotDuck();
	void ServerShotDuck_Implementation();

	UFUNCTION(BlueprintNativeEvent)
	void PerformShotFeedback();
	virtual void PerformShotFeedback_Implementation();

	UFUNCTION(BlueprintNativeEvent)
	void PerformResetFeedback();
	virtual void PerformResetFeedback_Implementation();

	UFUNCTION()
	void OnRepIsDown();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void ReceiveShot_Implementation();

protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const override;
};
