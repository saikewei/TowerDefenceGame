// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerDefenceGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "MonsterPaperFlipbookActor.h"
#include "SplinePathActor.h"

void ATowerDefenceGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	
	//查找处理本地玩家控制的Actor
	APlayerController* MyPlayerController = UGameplayStatics::GetPlayerController(this, 0);
	if (MyPlayerController)
	{
		//释放鼠标光标
		MyPlayerController->SetShowMouseCursor(true);
	}


	//设置定时器，定时刷新怪物
	FTimerHandle SpawnHandle;
	GetWorldTimerManager().SetTimer(SpawnHandle, this, &ATowerDefenceGameModeBase::SpawnMonster, FMath::RandRange(2, 5), true);
}

void ATowerDefenceGameModeBase::Tick(float DeltaTime)
{
}

void ATowerDefenceGameModeBase::SpawnMonster()
{
	//刷新怪物，并获取怪物对象本身
	FRotator Rotation = FRotator(180.f, 0.f, -90.f);
	UWorld* World = GetWorld();
	AMonsterPaperFlipbookActor* Monster = World->SpawnActor<AMonsterPaperFlipbookActor>(MonsterToSpawn, SpawnLocation, Rotation);
	//UE_LOG(LogTemp, Warning, TEXT("Spawn"));

	//获取splineActor对象
	TArray<AActor*> FoundPath;
	UGameplayStatics::GetAllActorsOfClass(World, ASplinePathActor::StaticClass(), FoundPath);
	//UE_LOG(LogTemp, Warning, TEXT("%d"), FoundPath.Num());

	//转换并获取其中的spline组件
	ASplinePathActor* MySpline = Cast<ASplinePathActor>(FoundPath[0]);
	if (MySpline)
	{
		Monster->SetPath(MySpline->GetSplinePath());
	}
}
