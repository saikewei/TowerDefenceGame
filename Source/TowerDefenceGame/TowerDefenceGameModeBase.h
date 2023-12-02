// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TowerDefenceGameModeBase.generated.h"

class AMonsterPaperFlipbookActor;
class ASplinePathActor;

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

	//每一个tick调用
	virtual void Tick(float DeltaTime) override;

	//刷新一个怪物
	void SpawnMonster();

	//刷新的怪物
	UPROPERTY(EditAnywhere)
	TSubclassOf<AMonsterPaperFlipbookActor> MonsterToSpawn;

	//怪物刷新位置
	UPROPERTY(EditAnywhere)
	FVector SpawnLocation;

	//本关卡的路径
	UPROPERTY(EditAnywhere)
	UClass* Path;
};
