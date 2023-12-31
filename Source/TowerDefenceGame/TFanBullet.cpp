// Fill out your copyright notice in the Description page of Project Settings.


#include "TFanBullet.h"

ATFanBullet::ATFanBullet()
{
    CollisionBox->SetCollisionObjectType(ECollisionChannel::ECC_Pawn); //修改碰撞类型，使其可以穿过障碍物
	BulletDamage = 15.0f;
}

void ATFanBullet::OnHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    //检查是否击中怪物
    AMonsterPaperFlipbookActor* Monster = Cast<AMonsterPaperFlipbookActor>(OtherActor);
    if (Monster)
    {
        UE_LOG(LogTemp, Warning, TEXT("Hit!"));
        //造成伤害
        Monster->GetDamage(BulletDamage);
    }
}
