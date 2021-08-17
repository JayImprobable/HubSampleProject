// Fill out your copyright notice in the Description page of Project Settings.


#include "RTTBomb.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"

// Sets default values
ARTTBomb::ARTTBomb()
{
	PrimaryActorTick.bCanEverTick = false;

	CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	
	RTTTextFeedback = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TextFeedback"));
	RTTTextFeedback->SetupAttachment(RootComponent);
	RTTTextFeedback->SetHorizontalAlignment(EHorizTextAligment::EHTA_Center);

	SetReplicates(true);
}

// Called when the game starts or when spawned
void ARTTBomb::BeginPlay()
{
	Super::BeginPlay();
	
}

void ARTTBomb::CallServer_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Server: Reached server, returning to client..."));
	ReturnToClient();
}

void ARTTBomb::ReturnToClient_Implementation()
{
	if (running && GetWorldTimerManager().IsTimerActive(timeOutHandle))
	{
		float rtt = UGameplayStatics::GetTimeSeconds(GetWorld()) - lastCallTime;
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, FString::Printf(TEXT("Returned to client; RTT: %f"), rtt));
		RTTTextFeedback->SetText(FString::Printf(TEXT("Last RTT: %f"), rtt));
		FinishExplosionVisual(rtt);
	}
}

void ARTTBomb::StartExplosionVisual_Implementation()
{
	//Blueprint Implemented Event;
}

void ARTTBomb::FinishExplosionVisual_Implementation(float RTT)
{
	//Blueprint Implemented Event;

	//Finishes timer
	running = false;

	if (GetWorldTimerManager().IsTimerActive(timeOutHandle))
		GetWorldTimerManager().ClearTimer(timeOutHandle);
}

void ARTTBomb::RunTimeOut()
{
	if (!running)
		return;

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, FString::Printf(TEXT("Request TimeOut")));
	RTTTextFeedback->SetText(FString::Printf(TEXT("Request TimeOut")));
	running = false;
	//FinishExplosionVisual(-1.0f);
}

// Called every frame
void ARTTBomb::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ARTTBomb::Activation_Implementation(AController* controller)
{	
	//If this is not called by a local player, return;
	if (!controller->IsValidLowLevel())
		return;

	//Set the net owner to be client-pawn if server.
	if (GetNetMode() == ENetMode::NM_ListenServer)
	{
		 if (!controller->IsLocalController())
		 {
			 SetOwner(controller->GetPawn());
		 }
	}

	if (GetNetMode() == ENetMode::NM_Client)
	{
		running = true;
		lastCallTime = UGameplayStatics::GetTimeSeconds(GetWorld());
		GetWorldTimerManager().SetTimer(timeOutHandle, this, &ARTTBomb::RunTimeOut, 1.0f, false, 10.0f);
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, TEXT("Client: call started on Client"));
		StartExplosionVisual();
		CallServer();
	}
	

}