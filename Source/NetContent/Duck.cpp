// Fill out your copyright notice in the Description page of Project Settings.


#include "Duck.h"
#include "Net/UnrealNetwork.h"
#include "Kismet/GameplayStatics.h"
#include "NetContentGameMode.h"

// Sets default values
ADuck::ADuck()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TimeToReturn = 6.0f;
	SetReplicates(true);
}

// Called when the game starts or when spawned
void ADuck::BeginPlay()
{
	Super::BeginPlay();

	if (bClientAuthority)
	{
		ANetContentGameMode* gm = Cast<ANetContentGameMode>(GetWorld()->GetAuthGameMode());
		if (gm)
			gm->SetOwnerToClient(this);
	}
	
}

void ADuck::DistributeShotAmongAllClients_Implementation()
{
	if (HasAuthority())
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Server: Perform visual feedback"));
	else
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, TEXT("Client: Perform visual feedback"));

	PerformShotFeedback();

	if (handle.IsValid())
		GetWorldTimerManager().ClearTimer(handle);
}

void ADuck::ServerResetDuck_Implementation()
{
	PerformResetFeedback();
}

void ADuck::ServerShotDuck_Implementation()
{
	if (HasAuthority())
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Server: Client has authority, so duck was shot."));
		
		bIsDown = true;
		DistributeShotAmongAllClients();

		if (handle.IsValid())
			GetWorldTimerManager().ClearTimer(handle);

		GetWorldTimerManager().SetTimer(handle, this, &ADuck::ServerResetDuck, TimeToReturn, false, TimeToReturn);
		// GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Server: Duck was shot"));
	}
		
}

void ADuck::PerformShotFeedback_Implementation()
{
	//Cosmetic Only
}

void ADuck::PerformResetFeedback_Implementation()
{
	//Cosmetic Only
}

void ADuck::OnRepIsDown()
{
	
}

// Called every frame
void ADuck::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADuck::ReceiveShot_Implementation()
{
	if (LocalFeedbackSystem != nullptr)
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), LocalFeedbackSystem, GetActorTransform(), true, EPSCPoolMethod::AutoRelease);
	if (HasAuthority() && GetNetMode() == ENetMode::NM_ListenServer && !bClientAuthority)
	{
		//if (bIsDown)
			//return;

		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Server: Duck was hit"));

		bIsDown = true;
		DistributeShotAmongAllClients();
		
		if (handle.IsValid())
			GetWorldTimerManager().ClearTimer(handle);

		GetWorldTimerManager().SetTimer(handle, this, &ADuck::ServerResetDuck, TimeToReturn, false, TimeToReturn);
		
	}
	
	if (GetNetMode() == ENetMode::NM_Client && bClientAuthority)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, TEXT("Client: This duck was hit on client"));
		ServerShotDuck();
	}
}

void ADuck::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ADuck, bIsDown);
}

