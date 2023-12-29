// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperFlipbookActor.h"
#include "MonsterPaperFlipbookActor.h"
#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"
#include "PaperFlipbookComponent.h"
#include "UpgradeSellMenu.h"
#include "ToweDefenceGameState.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundCue.h"
#include "TowerPaperFlipbookActor.generated.h"

/**
 *
 */
class UButton;
class ABullet;
class ATShitBullet;
class ATowerBase;
class UUpgradeSellMenu;

UCLASS()
class TOWERDEFENCEGAME_API ATowerPaperFlipbookActor : public APaperFlipbookActor
{
	GENERATED_BODY()
	friend class UUpgradeSellMenu;
	friend class ABullet;
	friend class ATShitBullet;
public:
	ATowerPaperFlipbookActor();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void BeginPlay() override;

	//选择目标怪物
	AMonsterPaperFlipbookActor* ChooseTargetMonster();

	//向目标攻击
	void FireAtTarget();

	//升级防御塔
	void UpgradeTower();

	//售出防御塔
	void SellTower();

	//处理点击事件
	virtual void NotifyActorOnClicked(FKey ButtonPressed = EKeys::LeftMouseButton) override;

	//设置自身UI可见
	void SetSelfVisibility(bool Visible);

	//设置其他UI不可见
	void SetOthersInvisible();

	//设置当前塔的塔基
	void SetMyBase(ATowerBase* const Base);

	//动画结束时调用
	void OnAnimationFinished();

	//设置可视化攻击范围大小
	void SetAttackRangeVisualScale();

protected:
	//防御塔攻击半径
	UPROPERTY(EditAnywhere, Category = "Basic")
	float AttackRange = 1000.f;

	//定义碰撞体
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* DetectionSphere;

	//怪物列表
	UPROPERTY(BlueprintReadWrite, Category = "Detection")
	TArray<AMonsterPaperFlipbookActor*> MonstersInRange;

	//目标怪物
	UPROPERTY(BlueprintReadWrite, Category = "Detection")
	AMonsterPaperFlipbookActor* TargetMonster;

	//子弹类的引用
	UPROPERTY(EditDefaultsOnly, Category = "Shooting")
	TSubclassOf<ABullet> BulletClass;

	//子弹发射的时间间隔
	UPROPERTY(EditAnywhere, Category = "Shooting")
	float FireRate;

	//定时器句柄
	FTimerHandle TimerHandle_FireRate;

	//防御塔旋转方向
	UPROPERTY(EditAnywhere, Category = "Rotation")
	FRotator TowerRotation;

	//防御塔外观
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UPaperFlipbookComponent* TowerFlipbook;

	//可视化攻击范围
	UPROPERTY(EditAnywhere)
	UPaperFlipbookComponent* AttackRangeVisual;

	//不同等级防御塔外观数组
	UPROPERTY(EditDefaultsOnly, Category = "Tower")
	TArray<UPaperFlipbook*> TowerLevelsFlipbooks;

	UPROPERTY(EditAnywhere,Category="Tower")
	bool IsVisible;

	//蓝图UI类
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUpgradeSellMenu> UpgradeSellMenuBlueprintClass;

	//创建指向菜单的指针
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tower")
	UUpgradeSellMenu* Menu;

	//当前防御塔的级别
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Tower")
	int32 CurrentLevel = 0;

	//防御塔升级费用
	UPROPERTY(EditAnywhere, Category = "LevelCost")
	TArray<int32>UpgradeCost;

	//防御塔出售费用
	UPROPERTY(EditAnywhere, Category = "LevelCost")
	TArray<int32>SellCost;

	//不同等级的防御塔攻击动画
	UPROPERTY(EditAnywhere, Category = "Tower Animation")
	TArray<UPaperFlipbook*> AttackAnimations;

	//生成此塔的塔基
	ATowerBase* MyBase;

	//攻击音频组件
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Audio", meta = (AllowPrivateAccess = "true"))
	UAudioComponent* AttackAudioComponent;

	//升级音频组件
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Audio", meta = (AllowPrivateAccess = "true"))
	UAudioComponent* UpgradeAudioComponent;

	//建造音频组件
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Audio", meta = (AllowPrivateAccess = "true"))
	UAudioComponent* BuildAudioComponent;

};
