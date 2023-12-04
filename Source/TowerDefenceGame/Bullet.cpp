// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"

ABullet::ABullet()
{
    PrimaryActorTick.bCanEverTick = true;
    // 设置初始速度和方向
    Speed = 2000.f;
    TravelDirection = FVector::ForwardVector;

    // 初始化碰撞组件
    CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
    CollisionBox->OnComponentHit.AddDynamic(this, &ABullet::OnHit);
    CollisionBox->SetupAttachment(RootComponent);

    // 初始化移动组件
    ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
    ProjectileMovement->UpdatedComponent = RootComponent;
    // 禁用重力
    ProjectileMovement->ProjectileGravityScale = 0.0f;

    BulletDamage = 10.f; // 伤害值
    DamageTypeClass = UDamageType::StaticClass(); // 伤害类型
}

void ABullet::InitializeBullet(const FVector& Direction)
{
    TravelDirection = Direction.GetSafeNormal();
    ProjectileMovement->Velocity = TravelDirection * ProjectileMovement->InitialSpeed;
    //UE_LOG(LogTemp, Warning, TEXT("%f %f %f"), TravelDirection.X, TravelDirection.Y, TravelDirection.Z);
}

void ABullet::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    // 检查是否击中怪物
    AMonsterPaperFlipbookActor* Monster = Cast<AMonsterPaperFlipbookActor>(OtherActor);
    if (Monster)
    {
        UE_LOG(LogTemp, Warning, TEXT("Hit!"));
        // 造成伤害
        UGameplayStatics::ApplyDamage(Monster, BulletDamage, nullptr, this, DamageTypeClass);

        // 销毁子弹
        Destroy();
    }
}

void ABullet::BeginPlay()
{
    Super::BeginPlay();
}

void ABullet::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    // 更新子弹位置
    FVector NewLocation = GetActorLocation() + (Speed * DeltaTime * TravelDirection);
    NewLocation.Z = 3.0f;
    //UE_LOG(LogTemp, Warning, TEXT("%f %f %f"), NewLocation.X, NewLocation.Y, NewLocation.Z);
    SetActorLocation(NewLocation);
}
