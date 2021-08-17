// Fill out your copyright notice in the Description page of Project Settings.


#include "ExtrapolationCanvas.h"
#include "Kismet/KismetMathLibrary.h"
#include "Net/UnrealNetwork.h"

// Sets default values
AExtrapolationCanvas::AExtrapolationCanvas()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SetReplicates(true);

	SetRootComponent(CreateDefaultSubobject<USceneComponent>(TEXT("Root")));

	SphereMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SphereMesh"));
	SphereMesh->SetupAttachment(GetRootComponent());
	SphereMesh->SetRelativeScale3D(FVector(0.2f, 0.001f, 0.2f));

	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("DirectionArrow"));
	Arrow->SetupAttachment(SphereMesh);
	Arrow->SetHiddenInGame(false);

	PickNewDirectionRate = 2.5f;
	AreaWidth = 500.0f;
	AreaHeight = 250.0f;
	
	Speed = 20.0f;
}

// Called when the game starts or when spawned
void AExtrapolationCanvas::BeginPlay()
{
	Super::BeginPlay();
	FTimerHandle handle;
	
	if (GetLocalRole() == ROLE_Authority)
	{
		GetWorldTimerManager().SetTimer(handle, this, &AExtrapolationCanvas::ChooseNewDirection, PickNewDirectionRate, true, 2.0f);
	}
}

void AExtrapolationCanvas::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AExtrapolationCanvas, velocity);
	
	//if(bReconciliate)
		DOREPLIFETIME(AExtrapolationCanvas, serverTargetLocation);
}

void AExtrapolationCanvas::ChooseNewDirection()
{
	serverTargetLocation = location;

	FVector direction;

	if (FMath::Abs(location.X) > AreaWidth * 0.4f || FMath::Abs(location.Z) > AreaHeight * 0.4f)
		direction = -location;
	else
		direction = UKismetMathLibrary::RandomUnitVector();
	

	direction = FVector(direction.X, 0.0f, direction.Z).GetSafeNormal();
	
	Arrow->SetRelativeRotation(UKismetMathLibrary::MakeRotFromX(direction));
	Arrow->SetArrowColor(FLinearColor((direction - FVector(0.5f, 0.5f, 0.5f)) * 2.0f));
	velocity = direction;
}

void AExtrapolationCanvas::OnRep_Velocity()
{
	Arrow->SetRelativeRotation(UKismetMathLibrary::MakeRotFromX(velocity));
	Arrow->SetArrowColor(FLinearColor(velocity));
}

void AExtrapolationCanvas::OnRep_Location()
{
	if(bReconciliate)
		location = serverTargetLocation;
}

// Called every frame
void AExtrapolationCanvas::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	location += velocity * DeltaTime * Speed;
	
	location = FVector(
		FMath::Clamp(location.X, -0.5f * AreaWidth, 0.5f * AreaWidth),
		0.0f,
		FMath::Clamp(location.Z, -0.5f * AreaHeight, 0.5f * AreaHeight)
	);

	SphereMesh->SetRelativeLocation(location);
}

void AExtrapolationCanvas::Activation_Implementation(AController* controller)
{
	location = FVector::ZeroVector;
}
