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
    // ����Ƿ���й���
    AMonsterPaperFlipbookActor* Monster = Cast<AMonsterPaperFlipbookActor>(OtherActor);
    if (Monster)
    {
        UE_LOG(LogTemp, Warning, TEXT("Hit!"));
        // ����˺�
        UGameplayStatics::ApplyDamage(Monster, BulletDamage, nullptr, this, DamageTypeClass);

        Decelerate(Monster);

        // �����ӵ�
        Destroy();
    }
}

void ATShitBullet::Decelerate(AMonsterPaperFlipbookActor* Monster)
{
    // ���������
    float OriginalSpeed = Monster->MovingSpeed;
    Monster->MovingSpeed /= 2;

    // ���ö�ʱ���ָ��ٶ�
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
