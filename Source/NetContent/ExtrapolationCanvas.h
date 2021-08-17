// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "Components/ArrowComponent.h"
#include "ExtrapolationCanvas.generated.h"

UCLASS()
class NETCONTENT_API AExtrapolationCanvas : public AActor, public IInteractable
{
	GENERATED_BODY()

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	UStaticMeshComponent* SphereMesh;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	UArrowComponent* Arrow;

public:	
	// Sets default values for this actor's properties
	AExtrapolationCanvas();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Canvas)
		float AreaHeight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Canvas)
		float AreaWidth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Canvas)
		float PickNewDirectionRate;
protected:
	UPROPERTY(BlueprintReadWrite)
		FVector location;

	UPROPERTY(ReplicatedUsing= OnRep_Location, BlueprintReadWrite)
		FVector serverTargetLocation;

	UPROPERTY(ReplicatedUsing=OnRep_Velocity, BlueprintReadWrite)
		FVector velocity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		uint8 bReconciliate:1;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const override;

	virtual void ChooseNewDirection();

	UFUNCTION()
		void OnRep_Velocity();

	UFUNCTION()
		void OnRep_Location();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Activation_Implementation(AController* controller) override;

};
