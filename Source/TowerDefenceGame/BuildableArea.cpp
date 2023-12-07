// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildableArea.h"

// Sets default values
ABuildableArea::ABuildableArea()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ABuildableArea::SetShutDownOthers()
{
	ShutDownOthers = true;
}

void ABuildableArea::RecoverShutDownOthers()
{
	ShutDownOthers = false;
}

bool ABuildableArea::GetShutDownOthers()
{
	return ShutDownOthers;
}

// Called when the game starts or when spawned
void ABuildableArea::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ABuildableArea::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

