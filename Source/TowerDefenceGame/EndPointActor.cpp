// Fill out your copyright notice in the Description page of Project Settings.


#include "EndPointActor.h"
#include "Components/BoxComponent.h"

// Sets default values
AEndPointActor::AEndPointActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CollisionBox = CreateDefaultSubobject<UBoxComponent>("CollisionBox");
}

void AEndPointActor::OnBeginOverlap(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFormSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("end"));
	OtherActor->Destroy();
}

// Called when the game starts or when spawned
void AEndPointActor::BeginPlay()
{
	Super::BeginPlay();

	//关联碰撞事件和处理函数
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AEndPointActor::OnBeginOverlap);
}

// Called every frame
void AEndPointActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

