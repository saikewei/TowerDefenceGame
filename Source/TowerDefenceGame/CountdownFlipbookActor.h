// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperFlipbookActor.h"
#include "CountdownFlipbookActor.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENCEGAME_API ACountdownFlipbookActor : public APaperFlipbookActor
{
	GENERATED_BODY()
public:
	virtual void BeginPlay()override;
protected:
	void SelfDestroy();
};
