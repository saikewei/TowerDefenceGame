// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerPaperFlipbookActor.h"
#include "TowerBase.h"

const int MaxLevel = 2;

ATowerPaperFlipbookActor::ATowerPaperFlipbookActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// 添加球形碰撞体，设定检测范围
	DetectionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("DetectionSphere"));
	DetectionSphere->SetupAttachment(RootComponent);
	DetectionSphere->SetSphereRadius(AttackRange);

	//// 添加盒体碰撞体，用于检测鼠标
	//CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	//CollisionBox->SetupAttachment(RootComponent);

	// 绑定触发事件
	DetectionSphere->OnComponentBeginOverlap.AddDynamic(this, &ATowerPaperFlipbookActor::OnMonsterEnterDetectionRange);
	DetectionSphere->OnComponentEndOverlap.AddDynamic(this, &ATowerPaperFlipbookActor::OnMonsterLeaveDetectionRange);
	UE_LOG(LogTemp, Warning, TEXT("Constructed!"));

	//设置发射频率
	FireRate = 0.2f; // 每0.2秒发射一次

	//调整防御塔方向
	TowerRotation = GetActorRotation();
	TowerRotation.Roll -= 90.0;
	SetActorRotation(TowerRotation);

	//设置动画组件
	TowerFlipbook = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("TowerFlipbook"));
	TowerFlipbook->SetupAttachment(RootComponent);

	//初始化等级
	CurrentLevel = 0;

	IsVisible = false;
	Menu = nullptr;
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

void ATowerPaperFlipbookActor::UpgradeTower()
{
	if (CurrentLevel < MaxLevel)
	{
		CurrentLevel++;
		// 更新防御塔属性：攻击力、攻击范围、攻击间隔等
		AttackRange += 200.f;
		if (FireRate >= 0.01f)
		{
			FireRate -= 0.1f;
			GetWorld()->GetTimerManager().SetTimer(TimerHandle_FireRate, this, &ATowerPaperFlipbookActor::FireAtTarget, FireRate, true);
		}
		//UE_LOG(LogTemp, Warning, TEXT("CLevel:%d"), CurrentLevel);
		// 更换防御塔的外观
		if (TowerLevelsFlipbooks.IsValidIndex(CurrentLevel - 1) && CurrentLevel - 1 >= 0)
		{
			TowerFlipbook->SetFlipbook(TowerLevelsFlipbooks[CurrentLevel - 1]);
			//UE_LOG(LogTemp, Warning, TEXT("Level:%d"), CurrentLevel);
		}

		// 花费金币
		AToweDefenceGameState* GameState = GetWorld()->GetGameState<AToweDefenceGameState>();
		if (CurrentLevel - 1 >= 0)
		{
			GameState->AddMoney(-UpgradeCost[CurrentLevel - 1]);
		}
	}
}

void ATowerPaperFlipbookActor::SellTower()
{
	// 返还金币
	AToweDefenceGameState* GameState = GetWorld()->GetGameState<AToweDefenceGameState>();
	GameState->AddMoney(SellCost[CurrentLevel]);
	// 销毁防御塔
	this->Destroy();
}

void ATowerPaperFlipbookActor::NotifyActorOnClicked(FKey ButtonPressed)
{
	this->SetSelfVisibility(!IsVisible);
	IsVisible = !IsVisible;
	SetOthersInvisible();
	UE_LOG(LogTemp, Warning, TEXT("Click"));
}

void ATowerPaperFlipbookActor::SetSelfVisibility(bool Visible)
{
	if (!Visible)
	{
		// 删除菜单
		if (Menu)
		{
			Menu->RemoveFromParent();
		}
		return;
	}
	else
	{
		// 创建菜单并生成到对应的位置
		Menu = CreateWidget<UUpgradeSellMenu>(GetWorld(), UpgradeSellMenuBlueprintClass);
		if (Menu)
		{
			Menu->TargetTower = this;
			// 获取玩家控制器
			APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
			FVector2D Position;
			Menu->BuildLocation = GetActorLocation();
			PlayerController->ProjectWorldLocationToScreen(Menu->BuildLocation, Position);
			Menu->AddToViewport();
			Menu->SetPositionInViewport(Position);
			UE_LOG(LogTemp, Warning, TEXT("Add!"));
		}
		return;
	}
}

void ATowerPaperFlipbookActor::SetOthersInvisible()
{
	// 获取关卡中所有的防御塔，并将除自身外的防御塔UI设置为不可见
	UWorld* World = GetWorld();
	TArray<AActor*> Towers;
	UGameplayStatics::GetAllActorsOfClass(World, ATowerPaperFlipbookActor::StaticClass(), Towers);
	for (AActor* Tower : Towers)
	{
		ATowerPaperFlipbookActor* Temp = Cast<ATowerPaperFlipbookActor>(Tower);
		if (Temp != this)
		{
			Temp->SetSelfVisibility(false);
		}
	}
}


