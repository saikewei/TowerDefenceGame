// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"

ABullet::ABullet()
{
    PrimaryActorTick.bCanEverTick = true;
    // ���ó�ʼ�ٶȺͷ���
    Speed = 2000.f;
    TravelDirection = FVector::ForwardVector;

    // ��ʼ����ײ���
    CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
    CollisionBox->OnComponentHit.AddDynamic(this, &ABullet::OnHit);
    CollisionBox->SetupAttachment(RootComponent);

    // ��ʼ���ƶ����
    ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
    ProjectileMovement->UpdatedComponent = RootComponent;
    // ��������
    ProjectileMovement->ProjectileGravityScale = 0.0f;

    BulletDamage = 10.f; // �˺�ֵ
    DamageTypeClass = UDamageType::StaticClass(); // �˺�����
}

void ABullet::InitializeBullet(const FVector& Direction)
{
    TravelDirection = Direction.GetSafeNormal();
    ProjectileMovement->Velocity = TravelDirection * ProjectileMovement->InitialSpeed;
    //UE_LOG(LogTemp, Warning, TEXT("%f %f %f"), TravelDirection.X, TravelDirection.Y, TravelDirection.Z);
}

void ABullet::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    // ����Ƿ���й���
    AMonsterPaperFlipbookActor* Monster = Cast<AMonsterPaperFlipbookActor>(OtherActor);
    if (Monster)
    {
        UE_LOG(LogTemp, Warning, TEXT("Hit!"));
        // ����˺�
        UGameplayStatics::ApplyDamage(Monster, BulletDamage, nullptr, this, DamageTypeClass);

        // �����ӵ�
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
    // �����ӵ�λ��
    FVector NewLocation = GetActorLocation() + (Speed * DeltaTime * TravelDirection);
    NewLocation.Z = 3.0f;
    //UE_LOG(LogTemp, Warning, TEXT("%f %f %f"), NewLocation.X, NewLocation.Y, NewLocation.Z);
    SetActorLocation(NewLocation);
}
