// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TowerPaperFlipbookActor.h"
#include "TBottle.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENCEGAME_API ATBottle : public ATowerPaperFlipbookActor
{
	GENERATED_BODY()
	
public:
	ATBottle();
	//转向目标怪物
	void RotateToTarget();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
