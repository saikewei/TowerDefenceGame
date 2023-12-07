// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterPaperFlipbookActor.h"
#include "Components/SplineComponent.h"
#include "Components/WidgetComponent.h"

AMonsterPaperFlipbookActor::AMonsterPaperFlipbookActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	MyPath = nullptr;
	MovingSpeed = 300.f;
	CurrentLocation = 0;
	HP = MAX_HP;
}

void AMonsterPaperFlipbookActor::SetPath(const USplineComponent* Path)
{
	//´«ÈëÂ·¾¶
	MyPath = Path;
}

void AMonsterPaperFlipbookActor::SetEndLocation(const FVector& End)
{
	EndLoaction = End;
}

void AMonsterPaperFlipbookActor::BeginPlay()
{
	Super::BeginPlay();
}

void AMonsterPaperFlipbookActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (MyPath != nullptr)
	{
		CurrentLocation += DeltaTime * MovingSpeed;
		FVector NewLocation = MyPath->GetLocationAtDistanceAlongSpline(CurrentLocation, ESplineCoordinateSpace::World);
		if (fabs(GetActorLocation().X - NewLocation.X) >= 1)
		{
			 if (GetActorLocation().X < NewLocation.X)
			 {
				SetActorRotation(FRotator(0.f, 0.f, -90.f));
			 }
			 else
			 {
				SetActorRotation(FRotator(180.f, 0.f, -90.f));
			 }
		}
		SetActorLocation(NewLocation);
	}
}

void AMonsterPaperFlipbookActor::GetDamage(float Damage)
{
	HP -= Damage;
	if (HP <= 0)
	{
		Destroy();
	}
}
