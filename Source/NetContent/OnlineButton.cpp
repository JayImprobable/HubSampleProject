// Fill out your copyright notice in the Description page of Project Settings.


#include "OnlineButton.h"

// Sets default values
AOnlineButton::AOnlineButton()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AOnlineButton::BeginPlay()
{
	Super::BeginPlay();
	
}
void AOnlineButton::PressTheButton_Implementation()
{
	if (!HasAuthority())
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Has not authority"));
	else
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Has authority!"));
		

	//UE_LOG(LogTemp, Warning, TEXT());
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("This function is running on server, only"));
	//ReturnToClient();
}

void AOnlineButton::ReturnToClient_Implementation()
{
//	UE_LOG(LogTemp, Warning, TEXT("Returned to client, finally"));
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Returned to client, finally"));
}


// Called every frame
void AOnlineButton::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

