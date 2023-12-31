// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "TowerDefenceSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENCEGAME_API UTowerDefenceSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite)
	bool Level2Availible;
};
