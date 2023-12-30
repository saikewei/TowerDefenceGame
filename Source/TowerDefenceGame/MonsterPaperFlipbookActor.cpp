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

AMonsterPaperFlipbookActor::AMonsterPaperFlipbookActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// ��ʼ����ײ���
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetupAttachment(RootComponent);

	MyPath = nullptr;
	MovingSpeed = 300.f;
	OriginalSpeed = 300.f;
	CurrentLocation = 0;
	IsAimed = false;
}

void AMonsterPaperFlipbookActor::SetPath(const USplineComponent* Path)
{
	//����·��
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
}

void AMonsterPaperFlipbookActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (MyPath != nullptr)
	{
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
}

void AMonsterPaperFlipbookActor::GetDamage(float Damage)
{
	HP -= Damage;
	if (HP <= 0)
	{
		//��õ�ǰ��Ϸ״̬
		AToweDefenceGameState* CurrentGameState = Cast<AToweDefenceGameState>(GetWorld()->GetGameState());
		if (CurrentGameState)
		{
			CurrentGameState->AddMoney(KillBonus);
		}
		MovingSpeed = 0.f;
		FTimerHandle animationTimer;
		GetWorldTimerManager().SetTimer(animationTimer, this, &AMonsterPaperFlipbookActor::Die, .3f, false);
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
	//���������ת����״̬
	ChangeIsAimed();
}

void AMonsterPaperFlipbookActor::NotifyActorOnInputTouchBegin(const ETouchIndex::Type FingerIndex)
{
	//ֱ�ӵ��õ���¼�������
	NotifyActorOnClicked();
}

void AMonsterPaperFlipbookActor::Die()
{
	Destroy();
}

void AMonsterPaperFlipbookActor::ChangeIsAimed()
{
	//��ת������״̬
	IsAimed = !IsAimed;

	//�ı��ǿ�����
	SetPinMarkVisibility(IsAimed);

	AToweDefenceGameState* CurrentState = Cast<AToweDefenceGameState>(GetWorld()->GetGameState());

	if (IsAimed)
	{
		//��������������ȡ������
		TArray<AActor*> OtherMonsters;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMonsterPaperFlipbookActor::StaticClass(), OtherMonsters);
		for (AActor* Monster : OtherMonsters)
		{
			// ������ϰ���������ײ����
			
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
		
		//���ñ�����״̬
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
		// ������ϰ���������ײ����
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