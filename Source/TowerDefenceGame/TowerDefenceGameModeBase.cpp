// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerDefenceGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "MonsterPaperFlipbookActor.h"
#include "SplinePathActor.h"
#include "TowerBase.h"
#include "Blueprint/UserWidget.h"
#include "ObstaclePaperFlipbookActor.h"

ATowerDefenceGameModeBase::ATowerDefenceGameModeBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	totalMonster = 0;
	currentWave = 1;
}

void ATowerDefenceGameModeBase::OpenPauseMenu()
{
	if (PauseMenu_Class != nullptr)
	{
		//�����˵����
		PauseMenuWidget = CreateWidget(GetWorld(), PauseMenu_Class);
		PauseMenuWidget->AddToViewport();
	}
}

void ATowerDefenceGameModeBase::GameLost()
{
	if(GameLostMenu_Class != nullptr)
	{
		//�����˵����
		GameLostMenuWidget = CreateWidget(GetWorld(), GameLostMenu_Class);
		GameLostMenuWidget->AddToViewport();
	}

	//��ͣ��Ϸ
	UGameplayStatics::SetGamePaused(GetWorld(), true);
}

void ATowerDefenceGameModeBase::GameWin()
{
	TArray<AActor*> RemainMonsters;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMonsterPaperFlipbookActor::StaticClass(), RemainMonsters);
	bool NoRemain = true;
	for (int32 i = 0; i < RemainMonsters.Num(); ++i)
	{
		if (!Cast<AObstaclePaperFlipbookActor>(RemainMonsters[i]))
			NoRemain = false;
	}

	if (NoRemain)
	{
		if (GameWinMenu_Class != nullptr)
		{
			//�����˵����
			GameWinMenuWidget = CreateWidget(GetWorld(), GameWinMenu_Class);
			GameWinMenuWidget->AddToViewport();
		}

		WaitForEnd.Invalidate();

		//��ͣ��Ϸ
		UGameplayStatics::SetGamePaused(GetWorld(), true);
	}
}

int32 ATowerDefenceGameModeBase::GetCurrentWave() const
{
	return currentWave;
}

int32 ATowerDefenceGameModeBase::GetCurrentLevelNum() const
{
	return levelNum;
}

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
	GetWorldTimerManager().SetTimer(SpawnHandle, this, &ATowerDefenceGameModeBase::SpawnMonster, FMath::RandRange(.7f, 1.2f), true, 3.f);

	//��ʼ��HUD���
	if (HUD_Class != nullptr)
	{
		HUDWidget = CreateWidget(GetWorld(), HUD_Class);
		HUDWidget->AddToViewport();

		//UE_LOG(LogTemp, Warning, TEXT("initialize HUD!"));
	}

	//OpenPauseMenu();
}

void ATowerDefenceGameModeBase::Tick(float DeltaTime)
{
	if (currentWave >= monsterPerWave.Num())
	{
		if (!GetWorldTimerManager().IsTimerActive(WaitForEnd))
		{
			GetWorldTimerManager().SetTimer(WaitForEnd, this, &ATowerDefenceGameModeBase::GameWin, .5f, true);
		}
	}
	else if (monsterPerWave.IsValidIndex(currentWave - 1) && totalMonster >= monsterPerWave[currentWave - 1])
	{
		GetWorldTimerManager().PauseTimer(SpawnHandle);

		totalMonster = 0;

		//���ò��м�ĵȴ�
		FTimerHandle waitTimer;
		GetWorldTimerManager().SetTimer(waitTimer, this, &ATowerDefenceGameModeBase::StartNextWave, 5, false);
		//UE_LOG(LogTemp, Warning, TEXT("%d"), totalMonster);
	}
}

void ATowerDefenceGameModeBase::SpawnMonster()
{
	totalMonster++;

	//ˢ�¹������ȡ���������
	FRotator Rotation = FRotator(180.f, 0.f, -90.f);
	UWorld* World = GetWorld();

	AMonsterPaperFlipbookActor* Monster = World->SpawnActor<AMonsterPaperFlipbookActor>(MonstersList[FMath::RandRange(0, MonstersList.Num() - 1)], SpawnLocation, Rotation);
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

void ATowerDefenceGameModeBase::StartNextWave()
{
	totalMonster = 0;
	++currentWave;
	GetWorldTimerManager().UnPauseTimer(SpawnHandle);
	UE_LOG(LogTemp, Warning, TEXT("new wave %d"), currentWave);
}
