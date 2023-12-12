// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterPaperFlipbookActor.h"
#include "Components/SplineComponent.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "Components/BoxComponent.h"
#include "ToweDefenceGameState.h"
#include "ToweDefenceGameState.h"

AMonsterPaperFlipbookActor::AMonsterPaperFlipbookActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// ��ʼ����ײ���
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetupAttachment(RootComponent);

	MyPath = nullptr;
	MovingSpeed = 300.f;
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
		Destroy();
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
			AMonsterPaperFlipbookActor* CastMonster = Cast< AMonsterPaperFlipbookActor>(Monster);
			if(CastMonster)
			{
				if (CastMonster != this && CastMonster->GetIsAimed())
				{
					CastMonster->ChangeIsAimed();
				}
			}
		}
		
		//���ñ�����״̬
		CurrentState->SetAimedTarget(this);
	}
	else
	{
		if (CurrentState)
		{
			CurrentState->SetAimedTarget(nullptr);
		}
	}
}

bool AMonsterPaperFlipbookActor::GetIsAimed() const
{
	return IsAimed;
}