// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperFlipbookActor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/BoxComponent.h"
#include "MonsterPaperFlipbookActor.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/DamageType.h"
#include "Bullet.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENCEGAME_API ABullet : public APaperFlipbookActor
{
	GENERATED_BODY()

public:
    ABullet();

    // 初始化子弹的属性
    void InitializeBullet(const FVector& Direction);

    // 子弹造成伤害的函数
    UFUNCTION()
    void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

protected:
    virtual void BeginPlay() override;

    // 子弹的速度
    UPROPERTY(EditAnywhere, Category = "Bullet")
    float Speed;

    // 子弹的方向
    FVector TravelDirection;

    // 每帧更新子弹的位置
    virtual void Tick(float DeltaTime) override;

    // 子弹的移动组件
    UPROPERTY(EditAnywhere, Category = "Movement")
    UProjectileMovementComponent* ProjectileMovement;

    // 子弹的碰撞组件
    UPROPERTY(EditAnywhere, Category = "Components")
    UBoxComponent* CollisionBox;

    // 子弹的伤害值
    UPROPERTY(BlueprintReadWrite, Category = "Damage")
    float BulletDamage;

    // 伤害类型
    UPROPERTY(EditAnywhere, Category = "Damage")
    TSubclassOf<UDamageType> DamageTypeClass;
};


