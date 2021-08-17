// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ShootTheDuckBooth.generated.h"

UCLASS()
class NETCONTENT_API AShootTheDuckBooth : public AActor
{
	GENERATED_BODY()
	
public: 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 bClientAuthority : 1;

public:	
	// Sets default values for this actor's properties
	AShootTheDuckBooth();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, Replicated)
	float timeInternal;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
