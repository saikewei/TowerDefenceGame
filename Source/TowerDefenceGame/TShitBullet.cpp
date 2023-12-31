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

void ATShitBullet::OnHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    // ����Ƿ���й���
    AMonsterPaperFlipbookActor* Monster = Cast<AMonsterPaperFlipbookActor>(OtherActor);
    if (Monster)
    {
        UE_LOG(LogTemp, Warning, TEXT("Hit!"));
        // ����˺�
        Monster->GetDamage(BulletDamage);

        Decelerate(Monster);

        // �����ӵ�
        Destroy();
    }
}

void ATShitBullet::Decelerate(AMonsterPaperFlipbookActor* Monster)
{
    // ���������
    float OriginalSpeed = Monster->OriginalSpeed;
    Monster->MovingSpeed = OriginalSpeed / 2;

    // ���ö�ʱ���ָ��ٶ�
    FTimerHandle ShitTimerHandle;
    FTimerDelegate TimerDelegate;
    TimerDelegate.BindLambda([Monster, OriginalSpeed]()
        {
            if (Monster)
            {
                Monster->MovingSpeed = OriginalSpeed;
            }
        });
    GetWorld()->GetTimerManager().SetTimer(ShitTimerHandle, TimerDelegate, DecerlerationTime, false);
}
