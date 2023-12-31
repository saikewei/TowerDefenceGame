// Fill out your copyright notice in the Description page of Project Settings.


#include "CountdownFlipbookActor.h"

void ACountdownFlipbookActor::BeginPlay()
{
	Super::BeginPlay();
	

	FTimerHandle countdownTimer;
	GetWorldTimerManager().SetTimer(countdownTimer, this, &ACountdownFlipbookActor::SelfDestroy, 2.7f, false);
	
}

void ACountdownFlipbookActor::SelfDestroy()
{
	Destroy();
}
