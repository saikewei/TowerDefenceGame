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

    // ��ʼ���ӵ�������
    void InitializeBullet(const FVector& Direction);

    // �ӵ�����˺��ĺ���
    UFUNCTION()
    void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

protected:
    virtual void BeginPlay() override;

    // �ӵ����ٶ�
    UPROPERTY(EditAnywhere, Category = "Bullet")
    float Speed;

    // �ӵ��ķ���
    FVector TravelDirection;

    // ÿ֡�����ӵ���λ��
    virtual void Tick(float DeltaTime) override;

    // �ӵ����ƶ����
    UPROPERTY(EditAnywhere, Category = "Movement")
    UProjectileMovementComponent* ProjectileMovement;

    // �ӵ�����ײ���
    UPROPERTY(EditAnywhere, Category = "Components")
    UBoxComponent* CollisionBox;

    // �ӵ����˺�ֵ
    UPROPERTY(BlueprintReadWrite, Category = "Damage")
    float BulletDamage;

    // �˺�����
    UPROPERTY(EditAnywhere, Category = "Damage")
    TSubclassOf<UDamageType> DamageTypeClass;
};


