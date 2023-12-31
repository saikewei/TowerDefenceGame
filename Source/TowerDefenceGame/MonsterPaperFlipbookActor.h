// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperFlipbookActor.h"
#include "MonsterPaperFlipbookActor.generated.h"

class USplineComponent;
class UUserwidget;
class UBoxComponent;
class ATShitBullet;
class UAudioComponent;
/**
 * 
 */

class UPaperFlipbookComponent;
UCLASS()
class TOWERDEFENCEGAME_API AMonsterPaperFlipbookActor : public APaperFlipbookActor
{
	GENERATED_BODY()

	friend class ATShitBullet;
public:
	AMonsterPaperFlipbookActor();
	
	//传入本关卡样条线路径
	void SetPath(const USplineComponent* Path);

	//在游戏开始时调用
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Damage") 
	void GetDamage(float Damage);

	UFUNCTION(BlueprintCallable, Category = "Bonus")
	int32 GetBonus()const;

	//改变当前被锁定状态
	void ChangeIsAimed();

	//获得当前被锁定状态
	bool GetIsAimed() const;

protected:
	//本角色所跟随的路径
	const USplineComponent* MyPath;

	//碰撞体
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UBoxComponent* CollisionBox;

	//移动速度
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MovingSpeed;

	//初始移速
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float OriginalSpeed;

	//当前在路径中的位置
	float CurrentLocation;

	//是否被锁定
	bool IsAimed;

	//怪物血量
	UPROPERTY(BlueprintReadOnly, Category = "Health")
	float HP;

	//怪物血量上限
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Health")
	float MAX_HP;

	//对萝卜造成的伤害
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Damage")
	float DamageForCarrot;

	//击杀得到的金币奖励
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Bonus")
	int32 KillBonus;

	//设置点击事件
	virtual void NotifyActorOnClicked(FKey ButtonPressed = EKeys::LeftMouseButton) override;

	//移动端的触摸事件
	virtual void NotifyActorOnInputTouchBegin(const ETouchIndex::Type FingerIndex)override;

	//设置头顶记号可见性
	UFUNCTION(BlueprintImplementableEvent, Category = "Pin")
	void SetPinMarkVisibility(bool IsVisable);

	//设置头顶记号可见性
	UFUNCTION(BlueprintImplementableEvent, Category = "HP")
	void SetHPBarPersentage(const float Persent);

	//设置血条可见性
	UFUNCTION(BlueprintImplementableEvent, Category = "HP")
	void SetHPBarMarkVisibility(bool IsVisable);

	//播放死亡动画
	void PlayDeadAnimation();

	//生成音频组件
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UAudioComponent* SpawnAudioComponent;

	//死亡音频组件
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UAudioComponent* DeathAudioComponent;

	//死亡动画
	UPROPERTY(EditAnywhere)
	UPaperFlipbookComponent* DeathAnimation;

	//踩屎动画
	UPROPERTY(EditAnywhere)
	UPaperFlipbookComponent* StepShitAnimation;

	//怪物外观
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UPaperFlipbookComponent* MonsterAnimation;

	//死亡处理
	virtual void Die();
};
