// Fill out your copyright notice in the Description page of Project Settings.

#include "TowerPaperFlipbookActor.h"


ATowerPaperFlipbookActor::ATowerPaperFlipbookActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// 添加球形碰撞体，设定检测范围
	DetectionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("DetectionSphere"));
	DetectionSphere->SetupAttachment(RootComponent);
	DetectionSphere->SetSphereRadius(AttackRange);

	// 绑定触发事件
	DetectionSphere->OnComponentBeginOverlap.AddDynamic(this, &ATowerPaperFlipbookActor::OnMonsterEnterDetectionRange);
	DetectionSphere->OnComponentEndOverlap.AddDynamic(this, &ATowerPaperFlipbookActor::OnMonsterLeaveDetectionRange);
	UE_LOG(LogTemp, Warning, TEXT("Constructed!"));

	// 设置发射频率
	FireRate = 0.2f; // 每0.2秒发射一次

	//调整防御塔方向
	TowerRotation = GetActorRotation();
	TowerRotation.Roll -= 90.0;
	SetActorRotation(TowerRotation);
}

void ATowerPaperFlipbookActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ChooseTargetMonster();
}

void ATowerPaperFlipbookActor::BeginPlay()
{
	Super::BeginPlay();
	// 设置定时器以定期调用 FireAtTarget
	GetWorld()->GetTimerManager().SetTimer(TimerHandle_FireRate, this, &ATowerPaperFlipbookActor::FireAtTarget, FireRate, true);
}

void ATowerPaperFlipbookActor::OnMonsterEnterDetectionRange(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AMonsterPaperFlipbookActor* MonsterActor = Cast<AMonsterPaperFlipbookActor>(OtherActor);
	if (MonsterActor)
	{
		// 将怪物添加到列表中
		MonstersInRange.AddUnique(MonsterActor);
	}
}

void ATowerPaperFlipbookActor::OnMonsterLeaveDetectionRange(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AMonsterPaperFlipbookActor* MonsterActor = Cast<AMonsterPaperFlipbookActor>(OtherActor);
	if (MonsterActor)
	{
		// 将怪物从列表中移除
		MonstersInRange.Remove(MonsterActor);
	}
}

AMonsterPaperFlipbookActor* ATowerPaperFlipbookActor::ChooseTargetMonster()
{
	AMonsterPaperFlipbookActor* ClosestMonster = nullptr;
	float MinDistance = MAX_FLT;

	// 遍历 MonstersInRange 数组，寻找最近的怪物
	for (AMonsterPaperFlipbookActor* Monster : MonstersInRange)
	{
		if (Monster)
		{
			float Distance = FVector::Dist(this->GetActorLocation(), Monster->GetActorLocation());
			if (Distance < MinDistance)
			{
				MinDistance = Distance;
				ClosestMonster = Monster;
			}
		}
	}
	TargetMonster = ClosestMonster;
	return TargetMonster;
}



void ATowerPaperFlipbookActor::FireAtTarget()
{
	if (TargetMonster)
	{
		FVector Direction = (TargetMonster->GetActorLocation() - GetActorLocation()).GetSafeNormal();
		ABullet* Bullet = GetWorld()->SpawnActor<ABullet>(BulletClass, GetActorLocation(), Direction.Rotation());
		if (Bullet)
		{
			Bullet->InitializeBullet(Direction);
			//UE_LOG(LogTemp, Warning, TEXT("%f %f %f"), Direction.X, Direction.Y, Direction.Z);
		}
	}
}

