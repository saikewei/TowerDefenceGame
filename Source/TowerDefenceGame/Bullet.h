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

    //��ʼ���ӵ�������
    void InitializeBullet(const FVector& Direction);

    //�ӵ�����˺��ĺ���
    UFUNCTION()
    virtual void OnHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    //�ӵ��Զ����ٺ���
    void AutoDestroy();
protected:
    virtual void BeginPlay() override;

    //ָ�����������ָ��
    UPROPERTY(EditAnywhere, Category = "Tower")
    ATowerPaperFlipbookActor* MyTower;

    //�ӵ����ٶ�
    UPROPERTY(EditAnywhere, Category = "Bullet")
    float Speed;

    //�ӵ��ķ���
    FVector TravelDirection;

    //ÿ֡�����ӵ���λ��
    virtual void Tick(float DeltaTime) override;

    //�ӵ�����ײ���
    UPROPERTY(EditAnywhere, Category = "Components")
    UBoxComponent* CollisionBox;

    //�ӵ����˺�ֵ
    UPROPERTY(BlueprintReadWrite, Category = "Damage")
    float BulletDamage;

    //�˺�����
    UPROPERTY(EditAnywhere, Category = "Damage")
    TSubclassOf<UDamageType> DamageTypeClass;

    //�ӵ����
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UPaperFlipbookComponent* BulletFlipbook;

    //��ͬ�ȼ��ӵ��������
    UPROPERTY(EditDefaultsOnly, Category = "Bullet")
    TArray<UPaperFlipbook*> BulletLevelsFlipbooks;

    //��ʱ�����
    FTimerHandle TimerHandle;
};


