// Fill out your copyright notice in the Description page of Project Settings.

#include "TowerPaperFlipbookActor.h"

const int MaxLevel = 2;

ATowerPaperFlipbookActor::ATowerPaperFlipbookActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// ���������ײ�壬�趨��ⷶΧ
	DetectionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("DetectionSphere"));
	DetectionSphere->SetupAttachment(RootComponent);
	DetectionSphere->SetSphereRadius(AttackRange);

	// �󶨴����¼�
	DetectionSphere->OnComponentBeginOverlap.AddDynamic(this, &ATowerPaperFlipbookActor::OnMonsterEnterDetectionRange);
	DetectionSphere->OnComponentEndOverlap.AddDynamic(this, &ATowerPaperFlipbookActor::OnMonsterLeaveDetectionRange);
	UE_LOG(LogTemp, Warning, TEXT("Constructed!"));

	//���÷���Ƶ��
	FireRate = 0.2f; // ÿ0.2�뷢��һ��

	//��������������
	TowerRotation = GetActorRotation();
	TowerRotation.Roll -= 90.0;
	SetActorRotation(TowerRotation);

	//���ö������
	TowerFlipbook = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("TowerFlipbook"));
	TowerFlipbook->SetupAttachment(RootComponent);

	//��ʼ���ȼ�
	CurrentLevel = 0;
}

void ATowerPaperFlipbookActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ChooseTargetMonster();
}

void ATowerPaperFlipbookActor::BeginPlay()
{
	Super::BeginPlay();
	// ���ö�ʱ���Զ��ڵ��� FireAtTarget
	GetWorld()->GetTimerManager().SetTimer(TimerHandle_FireRate, this, &ATowerPaperFlipbookActor::FireAtTarget, FireRate, true);
}

void ATowerPaperFlipbookActor::OnMonsterEnterDetectionRange(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AMonsterPaperFlipbookActor* MonsterActor = Cast<AMonsterPaperFlipbookActor>(OtherActor);
	if (MonsterActor)
	{
		// ��������ӵ��б���
		MonstersInRange.AddUnique(MonsterActor);
	}
}

void ATowerPaperFlipbookActor::OnMonsterLeaveDetectionRange(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AMonsterPaperFlipbookActor* MonsterActor = Cast<AMonsterPaperFlipbookActor>(OtherActor);
	if (MonsterActor)
	{
		// ��������б����Ƴ�
		MonstersInRange.Remove(MonsterActor);
	}
}

AMonsterPaperFlipbookActor* ATowerPaperFlipbookActor::ChooseTargetMonster()
{
	AMonsterPaperFlipbookActor* ClosestMonster = nullptr;
	float MinDistance = MAX_FLT;

	// ���� MonstersInRange ���飬Ѱ������Ĺ���
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

void ATowerPaperFlipbookActor::UpgradeTower()
{
	if (CurrentLevel < MaxLevel)
	{
		CurrentLevel++;
		// ���·��������ԣ���������������Χ�����������
		AttackRange += 200.f;
		if (FireRate >= 0.01f)
		{
			FireRate -= 0.05f;
		}

		// ���������������
		if (TowerLevelsFlipbooks.IsValidIndex(CurrentLevel))
		{
			TowerFlipbook->SetFlipbook(TowerLevelsFlipbooks[CurrentLevel - 1]);
		}
	}
}

void ATowerPaperFlipbookActor::SellTower()
{

}


