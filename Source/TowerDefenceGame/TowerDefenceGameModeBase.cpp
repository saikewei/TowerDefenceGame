// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerDefenceGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "MonsterPaperFlipbookActor.h"
#include "SplinePathActor.h"

void ATowerDefenceGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	
	//���Ҵ�������ҿ��Ƶ�Actor
	APlayerController* MyPlayerController = UGameplayStatics::GetPlayerController(this, 0);
	if (MyPlayerController)
	{
		//�ͷ������
		MyPlayerController->SetShowMouseCursor(true);
	}


	//���ö�ʱ������ʱˢ�¹���
	FTimerHandle SpawnHandle;
	GetWorldTimerManager().SetTimer(SpawnHandle, this, &ATowerDefenceGameModeBase::SpawnMonster, FMath::RandRange(2, 5), true);
}

void ATowerDefenceGameModeBase::Tick(float DeltaTime)
{
}

void ATowerDefenceGameModeBase::SpawnMonster()
{
	//ˢ�¹������ȡ���������
	FRotator Rotation = FRotator(180.f, 0.f, -90.f);
	UWorld* World = GetWorld();
	AMonsterPaperFlipbookActor* Monster = World->SpawnActor<AMonsterPaperFlipbookActor>(MonsterToSpawn, SpawnLocation, Rotation);
	//UE_LOG(LogTemp, Warning, TEXT("Spawn"));

	//��ȡsplineActor����
	TArray<AActor*> FoundPath;
	UGameplayStatics::GetAllActorsOfClass(World, ASplinePathActor::StaticClass(), FoundPath);
	//UE_LOG(LogTemp, Warning, TEXT("%d"), FoundPath.Num());

	//ת������ȡ���е�spline���
	ASplinePathActor* MySpline = Cast<ASplinePathActor>(FoundPath[0]);
	if (MySpline)
	{
		Monster->SetPath(MySpline->GetSplinePath());
	}
}
