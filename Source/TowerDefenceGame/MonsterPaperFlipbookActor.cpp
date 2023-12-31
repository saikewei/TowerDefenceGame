// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterPaperFlipbookActor.h"
#include "ObstaclePaperFlipbookActor.h"
#include "Components/SplineComponent.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "Components/BoxComponent.h"
#include "ToweDefenceGameState.h"
#include "TowerDefenceGameModeBase.h"
#include "Components/AudioComponent.h"
#include "PaperFlipbookComponent.h"


AMonsterPaperFlipbookActor::AMonsterPaperFlipbookActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// 初始化碰撞组件
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetupAttachment(RootComponent);

	//初始化音频组件
	SpawnAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("SpawnAudioComponent"));
	SpawnAudioComponent->SetupAttachment(RootComponent);

	DeathAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("DeathAudioComponent"));
	DeathAudioComponent->SetupAttachment(RootComponent);
	DeathAudioComponent->bAutoActivate = false;//自动激活，生成时播放这个音乐

	DeathAnimation = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("DeathAnimation"));
	DeathAnimation->SetupAttachment(RootComponent);
	DeathAnimation->SetVisibility(false);

	MonsterAnimation = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("MonsterAnimation"));
	MonsterAnimation->SetupAttachment(RootComponent);

	StepShitAnimation = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("StepShitAnimation"));
	StepShitAnimation->SetupAttachment(RootComponent);
	StepShitAnimation->SetVisibility(false);

	

	MyPath = nullptr;
	MovingSpeed = 300.f;
	OriginalSpeed = 300.f;
	CurrentLocation = 0;
	IsAimed = false;
}

void AMonsterPaperFlipbookActor::SetPath(const USplineComponent* Path)
{
	//传入路径
	MyPath = Path;
}

void AMonsterPaperFlipbookActor::BeginPlay()
{
	Super::BeginPlay();
	ATowerDefenceGameModeBase* curGamemode = Cast<ATowerDefenceGameModeBase>(GetWorld()->GetAuthGameMode());
	if (curGamemode)
	{
		MAX_HP *= .1f * curGamemode->GetCurrentWave();
	}
	HP = MAX_HP;

	SetPinMarkVisibility(false);
}

void AMonsterPaperFlipbookActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//怪物移动逻辑
	if (MyPath != nullptr)
	{
		//跟随路径移动
		CurrentLocation += DeltaTime * MovingSpeed;
		FVector NewLocation = MyPath->GetLocationAtDistanceAlongSpline(CurrentLocation, ESplineCoordinateSpace::World);
		if (fabs(GetActorLocation().X - NewLocation.X) >= 1)
		{
			 if (GetActorLocation().X < NewLocation.X)
			 {
				SetActorRotation(FRotator(0.f, 0.f, -90.f));
			 }
			 else
			 {
				SetActorRotation(FRotator(180.f, 0.f, -90.f));
			 }
		}
		SetActorLocation(NewLocation);
	}

	//怪物血条调整
	SetHPBarPersentage(HP / MAX_HP);
}

void AMonsterPaperFlipbookActor::GetDamage(float Damage)
{
	HP -= Damage;
	if (HP <= 0)
	{
		//获得当前游戏状态
		AToweDefenceGameState* CurrentGameState = Cast<AToweDefenceGameState>(GetWorld()->GetGameState());
		if (CurrentGameState)
		{
			//加钱
			CurrentGameState->AddMoney(KillBonus);
		}
		MovingSpeed = 0.f;
		SetHPBarMarkVisibility(false);
		StepShitAnimation->SetVisibility(false);
		//设置死亡倒计时，留一点时间播放动画
		FTimerHandle animationTimer;
		GetWorldTimerManager().SetTimer(animationTimer, this, &AMonsterPaperFlipbookActor::Die, .3f, false);
		DeathAudioComponent->Play();
		PlayDeadAnimation();
	}
}

int32 AMonsterPaperFlipbookActor::GetBonus() const
{
	return KillBonus;
}

void AMonsterPaperFlipbookActor::NotifyActorOnClicked(FKey ButtonPressed)
{
	UE_LOG(LogTemp, Warning, TEXT("clicked"));
	//被点击，反转锁定状态
	ChangeIsAimed();
}

void AMonsterPaperFlipbookActor::NotifyActorOnInputTouchBegin(const ETouchIndex::Type FingerIndex)
{
	//直接调用点击事件处理函数
	NotifyActorOnClicked();
}

void AMonsterPaperFlipbookActor::PlayDeadAnimation()
{
	SetPinMarkVisibility(false);
	MonsterAnimation->SetVisibility(false);
	DeathAnimation->SetVisibility(true);
	DeathAnimation->PlayFromStart();
	CollisionBox->DestroyComponent();
}

void AMonsterPaperFlipbookActor::Die()
{
	AToweDefenceGameState* MyState = GetWorld()->GetGameState<AToweDefenceGameState>();
	if (MyState)
	{
		MyState->AddKill();
	}
	Destroy();
}

void AMonsterPaperFlipbookActor::ChangeIsAimed()
{
	//反转被锁定状态
	IsAimed = !IsAimed;

	//改变标记可视性
	SetPinMarkVisibility(IsAimed);

	AToweDefenceGameState* CurrentState = Cast<AToweDefenceGameState>(GetWorld()->GetGameState());

	if (IsAimed)
	{
		//让其他被锁定的取消锁定
		TArray<AActor*> OtherMonsters;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMonsterPaperFlipbookActor::StaticClass(), OtherMonsters);
		for (AActor* Monster : OtherMonsters)
		{
			// 如果是障碍物，则更改碰撞设置
			
			AMonsterPaperFlipbookActor* CastMonster = Cast< AMonsterPaperFlipbookActor>(Monster);
			if(CastMonster)
			{
				if (CastMonster != this && CastMonster->GetIsAimed())
				{
					CastMonster->ChangeIsAimed();
				}
				AObstaclePaperFlipbookActor* ObstacleActor = Cast<AObstaclePaperFlipbookActor>(CastMonster);
				if (ObstacleActor)
				{
					ObstacleActor->ToggleCollision(false);
				}
			}
		}
		
		//设置被锁定状态
		CurrentState->SetAimedTarget(this);
		AObstaclePaperFlipbookActor* ObstacleActor = Cast<AObstaclePaperFlipbookActor>(this);
		if (ObstacleActor)
		{
			ObstacleActor->ToggleCollision(true);
		}
	}
	else
	{
		if (CurrentState)
		{
			CurrentState->SetAimedTarget(nullptr);
		}
		// 如果是障碍物，则更改碰撞设置
		AObstaclePaperFlipbookActor* ObstacleActor = Cast<AObstaclePaperFlipbookActor>(this);
		if (ObstacleActor)
		{
			ObstacleActor->ToggleCollision(false);
		}
	}
}

bool AMonsterPaperFlipbookActor::GetIsAimed() const
{
	return IsAimed;
}