// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SplinePathActor.generated.h"

class USplineComponent;

UCLASS()
class TOWERDEFENCEGAME_API ASplinePathActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASplinePathActor();

	//获取样条线组件
	const USplineComponent* GetSplinePath()const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//样条线组件
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	USplineComponent* SplinePath;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
