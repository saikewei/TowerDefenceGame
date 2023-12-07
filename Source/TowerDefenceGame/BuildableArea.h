// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BuildableArea.generated.h"

UCLASS()
class TOWERDEFENCEGAME_API ABuildableArea : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABuildableArea();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//初始防御塔建造花费
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 TowerCost;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};