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
        Decelerate(Monster);
        Monster->GetDamage(BulletDamage);
        // �����ӵ�
        Destroy();
    }
}

void ATShitBullet::Decelerate(AMonsterPaperFlipbookActor* Monster)
{
    if (Monster)
    {
        OriginalSpeed = Monster->OriginalSpeed;
        Monster->MovingSpeed = OriginalSpeed / 2;
        Monster->StepShitAnimation->SetVisibility(true);
        WeakMonster = Monster;

        // ���ö�ʱ��
        GetWorld()->GetTimerManager().SetTimer(ShitTimerHandle, this, &ATShitBullet::HandleDecelerationTimerExpired, DecerlerationTime, false);
    }
}

void ATShitBullet::HandleDecelerationTimerExpired()
{
    if (WeakMonster.IsValid())
    {
        WeakMonster->MovingSpeed = OriginalSpeed;
        WeakMonster->StepShitAnimation->SetVisibility(false);
    }
    GetWorld()->GetTimerManager().ClearTimer(ShitTimerHandle);
}

ATShitBullet::~ATShitBullet()
{
    // ���������������ʱ��
    if (GetWorld())
    {
        GetWorld()->GetTimerManager().ClearTimer(ShitTimerHandle);
    }
}