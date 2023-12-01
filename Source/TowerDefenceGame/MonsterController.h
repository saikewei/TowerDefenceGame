// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MonsterController.generated.h"

/**
 * 
 */


UCLASS()
class TOWERDEFENCEGAME_API AMonsterController : public AAIController
{
	GENERATED_BODY()
	
protected:

	//在游戏开始时调用
	virtual void BeginPlay() override;

	//每次移动到一个路径点后调用此函数
	virtual void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;
};
