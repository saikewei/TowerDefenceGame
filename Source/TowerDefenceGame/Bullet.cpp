// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"
#include "TowerPaperFlipbookActor.h"

ABullet::ABullet()
{
    PrimaryActorTick.bCanEverTick = true;
    //设置初始速度和方向
    Speed = 2000.f;
    TravelDirection = FVector::ForwardVector;

    //初始化碰撞组件
    CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
    CollisionBox->OnComponentHit.AddDynamic(this, &ABullet::OnHit);
    CollisionBox->SetupAttachment(RootComponent);

    BulletDamage = 10.f; //伤害值
    DamageTypeClass = UDamageType::StaticClass(); //伤害类型

    MyTower = nullptr;

    //设置动画组件
    BulletFlipbook = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("BulletFlipbook"));
    BulletFlipbook->SetupAttachment(RootComponent);
}

void ABullet::InitializeBullet(const FVector& Direction)
{
    TravelDirection = Direction.GetSafeNormal();
    //更换子弹的外观
    if (MyTower && BulletLevelsFlipbooks.IsValidIndex(MyTower->CurrentLevel - 1) && MyTower->CurrentLevel - 1 >= 0)
    {
        BulletFlipbook->SetFlipbook(BulletLevelsFlipbooks[MyTower->CurrentLevel - 1]);
        //UE_LOG(LogTemp, Warning, TEXT("Level:%d"), CurrentLevel);
    }
    //提高子弹伤害
    if (MyTower)
    {
        BulletDamage += MyTower->CurrentLevel * BulletDamage;
    }
    //UE_LOG(LogTemp, Warning, TEXT("%f %f %f"), TravelDirection.X, TravelDirection.Y, TravelDirection.Z);
}

void ABullet::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    //检查是否击中怪物
    AMonsterPaperFlipbookActor* Monster = Cast<AMonsterPaperFlipbookActor>(OtherActor);
    if (Monster)
    {
        UE_LOG(LogTemp, Warning, TEXT("Hit!"));
        //造成伤害
        UGameplayStatics::ApplyDamage(Monster, BulletDamage, nullptr, this, DamageTypeClass);

        //销毁子弹
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
    //设置5秒后自动销毁
    GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ABullet::AutoDestroy, 5.0f, false);
}

void ABullet::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    //更新子弹位置
    FVector NewLocation = GetActorLocation() + (Speed * DeltaTime * TravelDirection);
    NewLocation.Z = 3.0f;
    //UE_LOG(LogTemp, Warning, TEXT("%f %f %f"), NewLocation.X, NewLocation.Y, NewLocation.Z);
    SetActorLocation(NewLocation);
}
