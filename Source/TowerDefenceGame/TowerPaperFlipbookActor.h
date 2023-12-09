// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Bullet.h"
#include "PaperFlipbookActor.h"
#include "MonsterPaperFlipbookActor.h"
#include "Components/SphereComponent.h"
#include "PaperFlipbookComponent.h"
#include "TowerPaperFlipbookActor.generated.h"

/**
 *
 */
UCLASS()
class TOWERDEFENCEGAME_API ATowerPaperFlipbookActor : public APaperFlipbookActor
{
	GENERATED_BODY()

public:
	ATowerPaperFlipbookActor();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void BeginPlay() override;

	//检测怪物进入
	void OnMonsterEnterDetectionRange(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	//检测怪物离开
	void OnMonsterLeaveDetectionRange(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	// 选择目标怪物
	AMonsterPaperFlipbookActor* ChooseTargetMonster();

	//向目标攻击
	void FireAtTarget();

	//升级防御塔
	void UpgradeTower();

	//售出防御塔
	void SellTower();

protected:
	//防御塔攻击半径
	UPROPERTY(EditAnywhere, Category = "Basic")
	float AttackRange = 1000.f;

	//定义碰撞体
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* DetectionSphere;

	// 怪物列表
	UPROPERTY(BlueprintReadWrite, Category = "Detection")
	TArray<AMonsterPaperFlipbookActor*> MonstersInRange;

	// 目标怪物
	UPROPERTY(BlueprintReadWrite, Category = "Detection")
	AMonsterPaperFlipbookActor* TargetMonster = nullptr;

	// 子弹类的引用
	UPROPERTY(EditDefaultsOnly, Category = "Shooting")
	TSubclassOf<ABullet> BulletClass;

	// 子弹发射的时间间隔
	UPROPERTY(EditDefaultsOnly, Category = "Shooting")
	float FireRate;

	// 定时器句柄
	FTimerHandle TimerHandle_FireRate;

	// 防御塔旋转方向
	UPROPERTY(EditAnywhere, Category = "Rotation")
	FRotator TowerRotation;

	// 防御塔类
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UPaperFlipbookComponent* TowerFlipbook;

	// 不同等级防御塔外观数组
	UPROPERTY(EditDefaultsOnly, Category = "Tower")
	TArray<UPaperFlipbook*> TowerLevelsFlipbooks;

	// 当前防御塔的级别
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tower")
	int32 CurrentLevel = 0;

	UPROPERTY(EditAnywhere,Category="LevelCost")
	int32 LevelOneCost = 0;

	UPROPERTY(EditAnywhere, Category = "LevelCost")
	int32 LevelTwoCost = 0;

	UPROPERTY(EditAnywhere, Category = "SellAmount")
	int32 LevelZeroSold = 0;

	UPROPERTY(EditAnywhere, Category = "SellAmount")
	int32 LevelOneSold = 0;

	UPROPERTY(EditAnywhere, Category = "SellAmount")
	int32 LevelTwoSold = 0;

};
