// Fill out your copyright notice in the Description page of Project Settings.


#include "HitscanArea.h"
#include "Net/UnrealNetwork.h"
#include "Kismet/KismetMathLibrary.h"
#include "NetContentCharacter.h"
#include "DrawDebugHelpers.h"


// Sets default values
AHitscanArea::AHitscanArea()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SetReplicates(true);

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(SceneRoot);

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	BoxComponent->SetupAttachment(RootComponent);
	BoxComponent->InitBoxExtent(FVector(100.0f, 100.0f, 100.0f));
	
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AHitscanArea::OnOverlapBegin);
	BoxComponent->OnComponentEndOverlap.AddDynamic(this, &AHitscanArea::OnOverlapEnd);

	TargetPath = CreateDefaultSubobject<USplineComponent>(TEXT("SplineTargetPath"));
	TargetPath->SetClosedLoop(true);

	//Set default properties
	AmountOfDucks = 3;

	RotationSpeed = 50.0f;

}

// Called when the game starts or when spawned
void AHitscanArea::BeginPlay()
{
	Super::BeginPlay();
	InitDucks();
}

void AHitscanArea::InitDucks()
{
	if (DefaultDuckClass == nullptr)
		return;
	ducks.Empty();

	distance = TargetPath->GetSplineLength() / AmountOfDucks;

	for (int i = 0; i < AmountOfDucks; i++)
	{
		UHitscanDuckMeshComponent* currentDuck = NewObject<UHitscanDuckMeshComponent>(this, DefaultDuckClass);
		currentDuck->RegisterComponent();
		currentDuck->SetWorldLocation(TargetPath->GetLocationAtDistanceAlongSpline(i * distance, ESplineCoordinateSpace::World));
		currentDuck->SetWorldRotation(TargetPath->GetRotationAtDistanceAlongSpline(i * distance, ESplineCoordinateSpace::World));

		ducks.Add(currentDuck);

	}
}

void AHitscanArea::HitDuck_Implementation(int duckIndex)
{
	ducks[duckIndex]->bIsDown = true;
	UHitscanDuckMeshComponent* duck = ducks[duckIndex];
	FTimerHandle handle;
	GetWorldTimerManager().SetTimer(handle, FTimerDelegate::CreateLambda([duck]()
	{
		duck->bIsDown = false;
	}), 3.0, false);
}

// Called every frame
void AHitscanArea::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	timeInternal += DeltaTime;
	for (int i = 0; i < ducks.Num(); i++)
	{
		float currentDuckDistance = UKismetMathLibrary::GenericPercent_FloatFloat((i * distance + timeInternal * RotationSpeed), TargetPath->GetSplineLength());
		ducks[i]->SetWorldLocation(TargetPath->GetLocationAtDistanceAlongSpline(currentDuckDistance, ESplineCoordinateSpace::World));
	}
}

float AHitscanArea::GetCurrentTime()
{
	return timeInternal;
}

void AHitscanArea::ShootCall(FVector Location, FRotator Direction, float Time)
{
	// We can not rely on component's Mesh/Box Collision for this task, since we are taking the time the shot was made into account.
	// So we are handling collision manually with BoxLine Intersection.

	for (int i = 0; i < ducks.Num(); i++)
	{
		// First, we get a the collider bounding box.
		FBox box = ducks[i]->Bounds.GetBox();
		
		// And store its transform.
		FTransform oldTimeTransform = ducks[i]->GetComponentTransform();

		// We don't want the current transform, since we are going back in time and calculating the transform for with a time offset... 
		box = box.InverseTransformBy(oldTimeTransform);
		float currentDuckDistance = UKismetMathLibrary::GenericPercent_FloatFloat((i * distance + Time * RotationSpeed ), TargetPath->GetSplineLength());
		oldTimeTransform.SetLocation(TargetPath->GetLocationAtDistanceAlongSpline(currentDuckDistance, ESplineCoordinateSpace::World));

		// Then we re-transform the box with a virtual old transform.
		box = box.TransformBy(oldTimeTransform); 

		bool collided = FMath::LineBoxIntersection(box, Location, Location + Direction.Vector() * 2000, (Location + Direction.Vector() * 2000) - Location);

		//Use this to DrawDebug the box in time.
		DrawDebugBox(GetWorld(), box.GetCenter(), box.GetExtent(), FColor::Green, false, 0.35f);
		//UE_LOG(LogTemp, Log, TEXT("%s: %i collide:%s"), *FString(__FUNCTION__), i, collided ? TEXT("true") : TEXT("false"));
		
		if (collided)
			HitDuck(i);
	}

	DrawDebugLine(GetWorld(), Location, Location+Direction.Vector() * 2000, FColor::Red, false, 0.5f);
}

void AHitscanArea::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	ANetContentCharacter* character = Cast<ANetContentCharacter>(OtherActor);
	if (character != nullptr)
	{
		character->EnterHitscanArea(this);
	}
}

void AHitscanArea::OnOverlapEnd(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	ANetContentCharacter* character = Cast<ANetContentCharacter>(OtherActor);
	if (character != nullptr)
	{
		character->LeaveHitscanArea();
	}
}

void AHitscanArea::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AHitscanArea, timeInternal);
}

