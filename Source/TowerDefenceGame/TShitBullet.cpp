// Fill out your copyright notice in the Description page of Project Settings.


#include "TShitBullet.h"
#include "TowerPaperFlipbookActor.h"

ATShitBullet::ATShitBullet()
{
    BulletDamage = 5.0f;
	DecerlerationTime = 2.0f;
    if (MyTower)
    {
        DecerlerationTime *= MyTower->CurrentLevel;
    }
}

void ATShitBullet::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    // 检查是否击中怪物
    AMonsterPaperFlipbookActor* Monster = Cast<AMonsterPaperFlipbookActor>(OtherActor);
    if (Monster)
    {
        UE_LOG(LogTemp, Warning, TEXT("Hit!"));
        // 造成伤害
        UGameplayStatics::ApplyDamage(Monster, BulletDamage, nullptr, this, DamageTypeClass);

        Decelerate(Monster);

        // 销毁子弹
        Destroy();
    }
}

void ATShitBullet::Decelerate(AMonsterPaperFlipbookActor* Monster)
{
    // 给怪物减速
    float OriginalSpeed = Monster->MovingSpeed;
    Monster->MovingSpeed /= 2;

    // 设置定时器恢复速度
    FTimerHandle TimerHandle;
    FTimerDelegate TimerDelegate;
    TimerDelegate.BindLambda([Monster, OriginalSpeed]()
        {
            if (Monster)
            {
                Monster->MovingSpeed = OriginalSpeed;
            }
        });
    GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, DecerlerationTime, false);
}
