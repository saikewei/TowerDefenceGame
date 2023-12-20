// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TowerPaperFlipbookActor.h"
#include "TShit.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENCEGAME_API ATShit : public ATowerPaperFlipbookActor
{
	GENERATED_BODY()
public:
	ATShit();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
