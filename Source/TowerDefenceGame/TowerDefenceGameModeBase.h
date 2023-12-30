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
	ATowerDefenceGameModeBase();

	//打开暂停菜单
	void OpenPauseMenu();

	//游戏失败
	void GameLost();

	//游戏成功
	void GameWin();

	//获取当前怪物波次
	UFUNCTION(BlueprintCallable)
	int32 GetCurrentWave()const;

	//获取当前关卡序号
	UFUNCTION(BlueprintCallable)
	int32 GetCurrentLevelNum()const;

protected:
	//在游戏开始时调用
	virtual void BeginPlay() override;

	//每一个tick调用
	virtual void Tick(float DeltaTime) override;

	//刷新一个怪物
	void SpawnMonster();

	//当前波次
	int32 currentWave;

	//怪物刷新定时器
	FTimerHandle SpawnHandle;

	//判断游戏结束定时器
	FTimerHandle WaitForEnd;

	//每一波怪物数
	UPROPERTY(EditAnywhere)
	TArray<int32> monsterPerWave;

	//当前怪物数
	int32 totalMonster;

	//当前关卡
	UPROPERTY(EditAnywhere)
	int32 levelNum;

	//刷新的怪物
	UPROPERTY(EditAnywhere)
	TSubclassOf<AMonsterPaperFlipbookActor> MonsterToSpawn;

	//刷新的多种怪物
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<AMonsterPaperFlipbookActor>> MonstersList;

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

	//游戏成功菜单组件
	UPROPERTY(EditAnywhere, Category = "GameWinMenu")
	TSubclassOf<UUserWidget> GameWinMenu_Class;
	UUserWidget* GameWinMenuWidget;



	//更新下一波怪物
	void StartNextWave();
};
