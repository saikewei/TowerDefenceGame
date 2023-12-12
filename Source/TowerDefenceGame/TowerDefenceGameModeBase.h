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
public:
	//打开暂停菜单
	void OpenPauseMenu();

	//游戏失败
	void GameLost();

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

	//HUD组件
	UPROPERTY(EditAnywhere, Category = "UI HUD")
	TSubclassOf<UUserWidget> HUD_Class;
	UUserWidget* HUDWidget;

	//暂停菜单组件
	UPROPERTY(EditAnywhere, Category = "PauseMenu")
	TSubclassOf<UUserWidget> PauseMenu_Class;
	UUserWidget* PauseMenuWidget;

	//游戏失败菜单组件
	UPROPERTY(EditAnywhere, Category = "GameLostMenu")
	TSubclassOf<UUserWidget> GameLostMenu_Class;
	UUserWidget* GameLostMenuWidget;
};
