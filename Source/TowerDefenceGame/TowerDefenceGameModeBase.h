// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TowerDefenceGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENCEGAME_API ATowerDefenceGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:
	//在游戏开始时调用
	virtual void BeginPlay() override;

};
