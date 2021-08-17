// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Components/SplineComponent.h"
#include "HitscanDuckMeshComponent.h"
#include "HitscanArea.generated.h"

UCLASS()
class NETCONTENT_API AHitscanArea : public AActor
{
	GENERATED_BODY()
	
private:

	UPROPERTY(Category = Collision, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USceneComponent* SceneRoot;

protected: 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* BoxComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USplineComponent* TargetPath;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UHitscanDuckMeshComponent> DefaultDuckClass;

	UPROPERTY()
	TArray<UHitscanDuckMeshComponent*> ducks;

	UPROPERTY(Replicated)
	float timeInternal;

	float distance;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int AmountOfDucks;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RotationSpeed;	

public:	
	// Sets default values for this actor's properties
	AHitscanArea();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void InitDucks();

	UFUNCTION(NetMulticast, Reliable)
	void HitDuck(int duckIndex);
	virtual void HitDuck_Implementation(int duckIndex);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	float GetCurrentTime();

	UFUNCTION()
	void ShootCall(FVector Location, FRotator Direction, float Time);

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const override;
};
