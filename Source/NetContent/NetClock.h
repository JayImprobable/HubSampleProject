// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NetClock.generated.h"

UCLASS()
class NETCONTENT_API ANetClock : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANetClock();

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	UStaticMeshComponent* Plane;
	
	UPROPERTY(VisibleAnywhere, Replicated, BlueprintReadOnly, Category = "Clock")
	float Filling;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Clock")
	UMaterial* TemplateMaterial;

protected:
	UPROPERTY()
	UMaterialInstanceDynamic* currentMaterial;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
