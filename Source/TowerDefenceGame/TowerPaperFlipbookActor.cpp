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
	// ���������ײ�壬�趨��ⷶΧ
	DetectionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("DetectionSphere"));
	DetectionSphere->SetupAttachment(RootComponent);
	DetectionSphere->SetSphereRadius(AttackRange);

	//// ��Ӻ�����ײ�壬���ڼ�����
	//CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	//CollisionBox->SetupAttachment(RootComponent);

	UE_LOG(LogTemp, Warning, TEXT("Constructed!"));

	//���÷���Ƶ��
	FireRate = 0.2f; //ÿ0.2�뷢��һ��

	//��������������
	TowerRotation = GetActorRotation();
	TowerRotation.Roll -= 90.0;
	SetActorRotation(TowerRotation);

	//���ö������
	TowerFlipbook = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("TowerFlipbook"));
	TowerFlipbook->SetupAttachment(RootComponent);

	//��ʼ���ȼ�
	CurrentLevel = 0;

	//��ʼ��Ŀ�����ָ��
	TargetMonster = nullptr;

	//�󶨶������Ž�����ί��
	TowerFlipbook->OnFinishedPlaying.AddDynamic(this, &ATowerPaperFlipbookActor::OnAnimationFinished);

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
	// ���ö�ʱ���Զ��ڵ��� FireAtTarget
	GetWorld()->GetTimerManager().SetTimer(TimerHandle_FireRate, this, &ATowerPaperFlipbookActor::FireAtTarget, FireRate, true);
}

AMonsterPaperFlipbookActor* ATowerPaperFlipbookActor::ChooseTargetMonster()
{
	AMonsterPaperFlipbookActor* ClosestMonster = nullptr;
	float MinDistance = MAX_FLT;
	AToweDefenceGameState* CurrentState = Cast<AToweDefenceGameState>(GetWorld()->GetGameState());

	// ���ȿ�����û���ֶ�������Ŀ�꣬Ŀ���Ƿ��ڷ�Χ
	if (CurrentState->GetAimedTarget() != nullptr)
	{
		if (MonstersInRange.Find(CurrentState->GetAimedTarget()) != INDEX_NONE)
		{
			TargetMonster = CurrentState->GetAimedTarget();
			return TargetMonster;
		}
	}

	// ���� MonstersInRange ���飬Ѱ������Ĺ���
	for (AMonsterPaperFlipbookActor* Monster : MonstersInRange)
	{
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
		//���Ŷ�Ӧ�ȼ��Ĺ�������
		if (AttackAnimations.IsValidIndex(CurrentLevel))
		{
			TowerFlipbook->SetFlipbook(AttackAnimations[CurrentLevel]);
			TowerFlipbook->PlayFromStart();
			TowerFlipbook->SetLooping(false); //ȷ��������ѭ��
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
		DetectionSphere->SetSphereRadius(AttackRange);
		if (FireRate >= 0.01f)
		{
			FireRate -= 0.1f;
			GetWorld()->GetTimerManager().SetTimer(TimerHandle_FireRate, this, &ATowerPaperFlipbookActor::FireAtTarget, FireRate, true);
		}
		//UE_LOG(LogTemp, Warning, TEXT("CLevel:%d"), CurrentLevel);
		
		// ���������������
		if (TowerLevelsFlipbooks.IsValidIndex(CurrentLevel) && CurrentLevel >= 0)
		{
			TowerFlipbook->SetFlipbook(TowerLevelsFlipbooks[CurrentLevel]);
			//UE_LOG(LogTemp, Warning, TEXT("Level:%d"), CurrentLevel);
		}

		

		// ���ѽ��
		AToweDefenceGameState* GameState = GetWorld()->GetGameState<AToweDefenceGameState>();
		if (CurrentLevel - 1 >= 0)
		{
			GameState->AddMoney(-UpgradeCost[CurrentLevel - 1]);
		}
	}
}

void ATowerPaperFlipbookActor::SellTower()
{
	// �������
	AToweDefenceGameState* GameState = GetWorld()->GetGameState<AToweDefenceGameState>();
	GameState->AddMoney(SellCost[CurrentLevel]);
	
	//�ָ�������ʾ
	MyBase->SetIsTower(false);

	// ���ٷ�����
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
		// ɾ���˵�
		if (Menu)
		{
			Menu->RemoveFromParent();
		}
		return;
	}
	else
	{
		// �����˵������ɵ���Ӧ��λ��
		Menu = CreateWidget<UUpgradeSellMenu>(GetWorld(), UpgradeSellMenuBlueprintClass);
		if (Menu)
		{
			Menu->TargetTower = this;
			// ��ȡ��ҿ�����
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
	// ��ȡ�ؿ������еķ�������������������ķ�����UI����Ϊ���ɼ�
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

void ATowerPaperFlipbookActor::SetMyBase(ATowerBase* const Base)
{
	MyBase = Base;
	MyBase->SetIsTower(true);
}

void ATowerPaperFlipbookActor::OnAnimationFinished()
{
	//�л���Ĭ�϶������ǹ���״̬�Ķ�����
	TowerFlipbook->SetFlipbook(TowerLevelsFlipbooks[CurrentLevel]);
	UE_LOG(LogTemp, Warning, TEXT("SetBack"));
}


