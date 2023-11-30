// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MainCamera.generated.h"

UCLASS()
class TOWERDEFENCEGAME_API AMainCamera : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMainCamera();

protected:
	//指向摄像机对象的指针
	UPROPERTY(EditAnywhere)
	AActor* CameraPtr;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
