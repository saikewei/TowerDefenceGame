// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"
#include "TowerPaperFlipbookActor.h"

ABullet::ABullet()
{
    PrimaryActorTick.bCanEverTick = true;
    //���ó�ʼ�ٶȺͷ���
    Speed = 2000.f;
    TravelDirection = FVector::ForwardVector;

    //��ʼ����ײ���
    CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
    CollisionBox->OnComponentHit.AddDynamic(this, &ABullet::OnHit);
    CollisionBox->SetupAttachment(RootComponent);

    BulletDamage = 10.f; //�˺�ֵ
    DamageTypeClass = UDamageType::StaticClass(); //�˺�����

    MyTower = nullptr;

    //���ö������
    BulletFlipbook = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("BulletFlipbook"));
    BulletFlipbook->SetupAttachment(RootComponent);
}

void ABullet::InitializeBullet(const FVector& Direction)
{
    TravelDirection = Direction.GetSafeNormal();
    //�����ӵ������
    if (MyTower && BulletLevelsFlipbooks.IsValidIndex(MyTower->CurrentLevel - 1) && MyTower->CurrentLevel - 1 >= 0)
    {
        BulletFlipbook->SetFlipbook(BulletLevelsFlipbooks[MyTower->CurrentLevel - 1]);
        //UE_LOG(LogTemp, Warning, TEXT("Level:%d"), CurrentLevel);
    }
    //����ӵ��˺�
    if (MyTower)
    {
        BulletDamage += MyTower->CurrentLevel * BulletDamage;
    }
    //UE_LOG(LogTemp, Warning, TEXT("%f %f %f"), TravelDirection.X, TravelDirection.Y, TravelDirection.Z);
}

void ABullet::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    //����Ƿ���й���
    AMonsterPaperFlipbookActor* Monster = Cast<AMonsterPaperFlipbookActor>(OtherActor);
    if (Monster)
    {
        UE_LOG(LogTemp, Warning, TEXT("Hit!"));
        //����˺�
        UGameplayStatics::ApplyDamage(Monster, BulletDamage, nullptr, this, DamageTypeClass);

        //�����ӵ�
        Destroy();
    }
}

void ABullet::AutoDestroy()
{
    Destroy();
}

void ABullet::BeginPlay()
{
    Super::BeginPlay();
    //����5����Զ�����
    GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ABullet::AutoDestroy, 5.0f, false);
}

void ABullet::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    //�����ӵ�λ��
    FVector NewLocation = GetActorLocation() + (Speed * DeltaTime * TravelDirection);
    NewLocation.Z = 3.0f;
    //UE_LOG(LogTemp, Warning, TEXT("%f %f %f"), NewLocation.X, NewLocation.Y, NewLocation.Z);
    SetActorLocation(NewLocation);
}
