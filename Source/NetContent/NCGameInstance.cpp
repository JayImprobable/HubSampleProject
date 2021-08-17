// Fill out your copyright notice in the Description page of Project Settings.


#include "NCGameInstance.h"

float UNCGameInstance::GetPktLag() const
{
	return pktLag;
}

void UNCGameInstance::SetPktLag(float value)
{
	pktLag = value;
	FString command = FString::Printf(TEXT("Net PktLag=%f"), pktLag);
	GetWorld()->GetFirstPlayerController()->ConsoleCommand(command);
	OnPktLagChange.Broadcast(value);
}

float UNCGameInstance::PktLagVariance() const
{
	return pktLagVariance;
}

void UNCGameInstance::SetPktLagVariance(float value)
{
	pktLagVariance = value;
	FString command = FString::Printf(TEXT("Net PktLagVariance=%f"), pktLagVariance);
	GetWorld()->GetFirstPlayerController()->ConsoleCommand(command);
	OnPktLagVarianceChange.Broadcast(value);
}

float UNCGameInstance::GetPktLoss() const
{
	return pktLoss;
}

void UNCGameInstance::SetPktLoss(float value)
{
	pktLoss = value;
	FString command = FString::Printf(TEXT("Net PktLoss=%f"), pktLoss);
	GetWorld()->GetFirstPlayerController()->ConsoleCommand(command);
	OnPktLossChange.Broadcast(value);
}
