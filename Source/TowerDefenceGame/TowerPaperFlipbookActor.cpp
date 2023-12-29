// Fill out your copyright notice in the Description page of Project Settings.

#include "TowerPaperFlipbookActor.h"
#include "ObstaclePaperFlipbookActor.h"
#include "TowerBase.h"
#include "Bullet.h"

const int MaxLevel = 2;

ATowerPaperFlipbookActor::ATowerPaperFlipbookActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//添加球形碰撞体，设定检测范围
	DetectionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("DetectionSphere"));
	DetectionSphere->SetupAttachment(RootComponent);
	DetectionSphere->SetSphereRadius(AttackRange);

	//设置发射频率
	FireRate = 0.2f; //每0.2秒发射一次

	//调整防御塔方向
	TowerRotation = GetActorRotation();
	TowerRotation.Roll -= 90.0;
	SetActorRotation(TowerRotation);

	//设置动画组件
	TowerFlipbook = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("TowerFlipbook"));
	TowerFlipbook->SetupAttachment(RootComponent);

	AttackRangeVisual = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("AttackRangeVisual"));
	AttackRangeVisual->SetupAttachment(RootComponent);
	AttackRangeVisual->SetVisibility(false); // 默认设置为不可见

	//初始化等级
	CurrentLevel = 0;

	//初始化目标怪物指针
	TargetMonster = nullptr;

	//初始化音频组件
	AttackAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AttackAudioComponent"));
	AttackAudioComponent->SetupAttachment(RootComponent);
	AttackAudioComponent->bAutoActivate = false;//禁用自动激活，防止防御塔生成时播放这个音乐

	BuildAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("BuildAudioComponent"));
	BuildAudioComponent->SetupAttachment(RootComponent);
	BuildAudioComponent->bAutoActivate = true;

	UpgradeAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("UpgradeAudioComponent"));
	UpgradeAudioComponent->SetupAttachment(RootComponent);
	UpgradeAudioComponent->bAutoActivate = false;

	IsVisible = false;
	Menu = nullptr;
	MyBase = nullptr;
}

void ATowerPaperFlipbookActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ChooseTargetMonster();
}

void ATowerPaperFlipbookActor::BeginPlay()
{
	Super::BeginPlay();
	SetAttackRangeVisualScale();
	//设置定时器以定期调用FireAtTarget
	GetWorld()->GetTimerManager().SetTimer(TimerHandle_FireRate, this, &ATowerPaperFlipbookActor::FireAtTarget, FireRate, true);
}

AMonsterPaperFlipbookActor* ATowerPaperFlipbookActor::ChooseTargetMonster()
{
	AMonsterPaperFlipbookActor* ClosestMonster = nullptr;
	float MinDistance = MAX_FLT;
	AToweDefenceGameState* CurrentState = Cast<AToweDefenceGameState>(GetWorld()->GetGameState());

	//首先看看有没有手动锁定的目标，目标是否在范围
	if (CurrentState->GetAimedTarget() != nullptr)
	{
		if (MonstersInRange.Find(CurrentState->GetAimedTarget()) != INDEX_NONE)
		{
			TargetMonster = CurrentState->GetAimedTarget();
			return TargetMonster;
		}
	}

	//遍历MonstersInRange数组，寻找最近的怪物
	for (auto It = MonstersInRange.CreateIterator(); It; ++It)
	{
		AMonsterPaperFlipbookActor* Monster = *It;
		if (Monster && !Cast<AObstaclePaperFlipbookActor>(Monster))
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
			Bullet->MyTower = this;
			Bullet->InitializeBullet(Direction);
			//UE_LOG(LogTemp, Warning, TEXT("%f %f %f"), Direction.X, Direction.Y, Direction.Z);
		}
		//播放对应等级的攻击动画
		if (AttackAnimations.IsValidIndex(CurrentLevel))
		{
			TowerFlipbook->SetFlipbook(AttackAnimations[CurrentLevel]);
			TowerFlipbook->PlayFromStart();
			TowerFlipbook->SetLooping(false);//确保动画不循环
		}
		//停止当前播放的音效,防止攻击速度过快导致后续音效无法播放
		if (AttackAudioComponent->IsPlaying())
		{
			AttackAudioComponent->Stop();
		}
		//播放攻击音效
		if (AttackAudioComponent && AttackAudioComponent->IsReadyForOwnerToAutoDestroy())
		{
			AttackAudioComponent->Play();
		}
	}
}

void ATowerPaperFlipbookActor::UpgradeTower()
{
	if (CurrentLevel < MaxLevel)
	{
		CurrentLevel++;
		//更新防御塔属性：攻击力、攻击范围、攻击间隔等
		AttackRange += 200.f; 
		DetectionSphere->SetSphereRadius(AttackRange);
		SetAttackRangeVisualScale();
		AttackRangeVisual->SetVisibility(false);
		if (FireRate >= 0.01f)
		{
			FireRate -= 0.1f;
			GetWorld()->GetTimerManager().SetTimer(TimerHandle_FireRate, this, &ATowerPaperFlipbookActor::FireAtTarget, FireRate, true);
		}
		//UE_LOG(LogTemp, Warning, TEXT("CLevel:%d"), CurrentLevel);
		
		//更换防御塔的外观
		if (TowerLevelsFlipbooks.IsValidIndex(CurrentLevel) && CurrentLevel >= 0)
		{
			TowerFlipbook->SetFlipbook(TowerLevelsFlipbooks[CurrentLevel]);
			//UE_LOG(LogTemp, Warning, TEXT("Level:%d"), CurrentLevel);
		}
		if (UpgradeAudioComponent->IsPlaying())
		{
			UpgradeAudioComponent->Stop();
		}
		//播放升级音效
		if (UpgradeAudioComponent && UpgradeAudioComponent->IsReadyForOwnerToAutoDestroy())
		{
			UpgradeAudioComponent->Play();
		}

		//花费金币
		AToweDefenceGameState* GameState = GetWorld()->GetGameState<AToweDefenceGameState>();
		if (CurrentLevel - 1 >= 0)
		{
			GameState->AddMoney(-UpgradeCost[CurrentLevel - 1]);
		}
	}
}

void ATowerPaperFlipbookActor::SellTower()
{
	//返还金币
	AToweDefenceGameState* GameState = GetWorld()->GetGameState<AToweDefenceGameState>();
	GameState->AddMoney(SellCost[CurrentLevel]);
	
	//恢复塔基显示
	MyBase->SetIsTower(false);

	//销毁防御塔
	this->Destroy();
}

void ATowerPaperFlipbookActor::NotifyActorOnClicked(FKey ButtonPressed)
{
	this->SetSelfVisibility(!IsVisible);
	//切换攻击范围的可见性
	bool bIsCurrentlyVisible = AttackRangeVisual->IsVisible();
	AttackRangeVisual->SetVisibility(!bIsCurrentlyVisible);
	IsVisible = !IsVisible;
	SetOthersInvisible();
	//UE_LOG(LogTemp, Warning, TEXT("ClickTower"));
}

void ATowerPaperFlipbookActor::NotifyActorOnInputTouchBegin(const ETouchIndex::Type FingerIndex)
{
	//直接调用点击事件处理函数
	NotifyActorOnClicked();
}

void ATowerPaperFlipbookActor::SetSelfVisibility(bool Visible)
{
	if (!Visible)
	{
		//删除菜单
		if (Menu)
		{
			Menu->RemoveFromParent();
		}
		return;
	}
	else
	{
		//创建菜单并生成到对应的位置
		Menu = CreateWidget<UUpgradeSellMenu>(GetWorld(), UpgradeSellMenuBlueprintClass);
		if (Menu)
		{
			Menu->TargetTower = this;
			//获取玩家控制器
			APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
			FVector2D Position;
			Menu->BuildLocation = GetActorLocation();
			PlayerController->ProjectWorldLocationToScreen(Menu->BuildLocation, Position);
			Menu->AddToViewport();
			Menu->SetPositionInViewport(Position);
		}
		return;
	}
}

void ATowerPaperFlipbookActor::SetOthersInvisible()
{
	//获取关卡中所有的防御塔，并将除自身外的防御塔UI设置为不可见
	UWorld* World = GetWorld();
	TArray<AActor*> Towers;
	UGameplayStatics::GetAllActorsOfClass(World, ATowerPaperFlipbookActor::StaticClass(), Towers);
	for (AActor* Tower : Towers)
	{
		ATowerPaperFlipbookActor* Temp = Cast<ATowerPaperFlipbookActor>(Tower);
		if (Temp != this)
		{
			Temp->SetSelfVisibility(false);
			Temp->AttackRangeVisual->SetVisibility(false);
		}
	}
}

void ATowerPaperFlipbookActor::SetMyBase(ATowerBase* const Base)
{
	MyBase = Base;
	MyBase->SetIsTower(true);
}

void ATowerPaperFlipbookActor::SetAttackRangeVisualScale()
{
	const float OriginalDiameter = 330.f;

	//计算缩放比例
	float ScaleFactor = AttackRange / OriginalDiameter;

	//设置 PaperFlipbook 的缩放
	FVector NewScale(ScaleFactor, ScaleFactor, ScaleFactor);
	AttackRangeVisual->SetWorldScale3D(NewScale);
}


