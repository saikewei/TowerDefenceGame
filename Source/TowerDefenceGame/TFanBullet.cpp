// Fill out your copyright notice in the Description page of Project Settings.


#include "TFanBullet.h"

ATFanBullet::ATFanBullet()
{
    CollisionBox->SetCollisionObjectType(ECollisionChannel::ECC_Pawn); //�޸���ײ���ͣ�ʹ����Դ����ϰ���
	BulletDamage = 15.0f;
}

void ATFanBullet::OnHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    //����Ƿ���й���
    AMonsterPaperFlipbookActor* Monster = Cast<AMonsterPaperFlipbookActor>(OtherActor);
    if (Monster)
    {
        UE_LOG(LogTemp, Warning, TEXT("Hit!"));
        //����˺�
        Monster->GetDamage(BulletDamage);
    }
}
