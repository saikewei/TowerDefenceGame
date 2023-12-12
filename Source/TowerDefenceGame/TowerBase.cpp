// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerBase.h"
#include "BuildMenu.h"

// Sets default values
ATowerBase::ATowerBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	IsTower = false;
	IsPlusSign = false;
	Menu = nullptr;
	// ��ʼ����ײ���
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ATowerBase::BeginPlay()
{
	Super::BeginPlay();
}

void ATowerBase::NotifyActorOnClicked(FKey ButtonPressed)
{
	if (!IsTower)
	{
		this->SetBaseVisibility(!IsPlusSign);//��������ɼ���
		SetOtherBasesInvisible();//ʹ�����������ɼ�
	}
}

void ATowerBase::SetOtherBasesInvisible()
{
	// ��ȡ�ؿ������е����������������������������Ϊ���ɼ�
	UWorld* World = GetWorld(); 
	TArray<AActor*> Bases;
	UGameplayStatics::GetAllActorsOfClass(World, ATowerBase::StaticClass(), Bases);
	for (AActor* Base : Bases)
	{
		ATowerBase* Temp = Cast<ATowerBase>(Base);
		if (Temp != this)
		{
			Temp->SetBaseVisibility(false);
		}
	}
}

// Called every frame
void ATowerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void ATowerBase::SetBaseVisibility(bool Visible)
{
	IsPlusSign = Visible;
	// ���üӺű�־�ɼ���
	this->ToggleSignVsibility(IsPlusSign);
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
		Menu = CreateWidget<UBuildMenu>(GetWorld(), BuildMenuBlueprintClass);
		if (Menu)
		{
			// ��ȡ��ҿ�����
			APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
			FVector2D Position;
			Menu->BuildLocation = GetActorLocation();
			Menu->TargetBase = this;
			PlayerController->ProjectWorldLocationToScreen(Menu->BuildLocation, Position);
			Menu->AddToViewport();
			Menu->SetPositionInViewport(Position);
		}
		return;
	}
}

void ATowerBase::SetIsTower(bool NewIsTower)
{
	IsTower = NewIsTower;
}

