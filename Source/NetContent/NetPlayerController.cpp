// Fill out your copyright notice in the Description page of Project Settings.


#include "NetPlayerController.h"
#include "Kismet/GameplayStatics.h"

void ANetPlayerController::PressTheButton_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("This function is running on server"));
	ReturnToClient();
}

void ANetPlayerController::ReturnToClient_Implementation()
{
	float rtt =	UGameplayStatics::GetTimeSeconds(GetWorld()) - _lastCallTime;
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("RTT: %f"), rtt));
}
