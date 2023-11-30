// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCamera.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMainCamera::AMainCamera()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMainCamera::BeginPlay()
{
	Super::BeginPlay();

	//查找处理本地玩家控制的Actor
	APlayerController* MyPlayerController = UGameplayStatics::GetPlayerController(this, 0);
	if (CameraPtr != nullptr && MyPlayerController && MyPlayerController->GetViewTarget())
	{
		//设置摄像机
		MyPlayerController->SetViewTarget(CameraPtr);
	}
}

// Called every frame
void AMainCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

