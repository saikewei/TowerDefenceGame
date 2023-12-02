// Fill out your copyright notice in the Description page of Project Settings.


#include "SplinePathActor.h"
#include "Components/SplineComponent.h"

// Sets default values
ASplinePathActor::ASplinePathActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//生成样条线实例
	SplinePath = CreateDefaultSubobject<USplineComponent>("Spline");
}

const USplineComponent* ASplinePathActor::GetSplinePath() const
{
	const USplineComponent* Path = SplinePath;
	return Path;
}

// Called when the game starts or when spawned
void ASplinePathActor::BeginPlay()
{
	Super::BeginPlay();

	//创建初始起始点
	SplinePath->AddSplinePoint(FVector(0, 0, 0), ESplineCoordinateSpace::Local);
	SplinePath->AddSplinePoint(FVector(500, 0, 0), ESplineCoordinateSpace::Local);
}

// Called every frame
void ASplinePathActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

