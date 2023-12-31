// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperFlipbookActor.h"
#include "PaperFlipbookComponent.h"
#include "Components/BoxComponent.h"
#include "MonsterPaperFlipbookActor.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/DamageType.h"
#include "Bullet.generated.h"

/**
 * 
 */
class ATowerPaperFlipbookActor;

UCLASS()
class TOWERDEFENCEGAME_API ABullet : public APaperFlipbookActor
{
	GENERATED_BODY()
    friend class ATowerPaperFlipbookActor;
public:
    ABullet();

    //初始化子弹的属性
    void InitializeBullet(const FVector& Direction);

    //子弹造成伤害的函数
    UFUNCTION()
    virtual void OnHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    //子弹自动销毁函数
    void AutoDestroy();
protected:
    virtual void BeginPlay() override;

    //指向其防御塔的指针
    UPROPERTY(EditAnywhere, Category = "Tower")
    ATowerPaperFlipbookActor* MyTower;

    //子弹的速度
    UPROPERTY(EditAnywhere, Category = "Bullet")
    float Speed;

    //子弹的方向
    FVector TravelDirection;

    //每帧更新子弹的位置
    virtual void Tick(float DeltaTime) override;

    //子弹的碰撞组件
    UPROPERTY(EditAnywhere, Category = "Components")
    UBoxComponent* CollisionBox;

    //子弹的伤害值
    UPROPERTY(BlueprintReadWrite, Category = "Damage")
    float BulletDamage;

    //伤害类型
    UPROPERTY(EditAnywhere, Category = "Damage")
    TSubclassOf<UDamageType> DamageTypeClass;

    //子弹外观
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UPaperFlipbookComponent* BulletFlipbook;

    //不同等级子弹外观数组
    UPROPERTY(EditDefaultsOnly, Category = "Bullet")
    TArray<UPaperFlipbook*> BulletLevelsFlipbooks;

    //定时器句柄
    FTimerHandle TimerHandle;
};


