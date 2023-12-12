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
	// 初始化碰撞组件
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
		this->SetBaseVisibility(!IsPlusSign);//设置自身可见性
		SetOtherBasesInvisible();//使其他塔基不可见
	}
}

void ATowerBase::SetOtherBasesInvisible()
{
	// 获取关卡中所有的塔基，并将除自身外的塔基设置为不可见
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
	// 设置加号标志可见性
	this->ToggleSignVsibility(IsPlusSign);
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
		Menu = CreateWidget<UBuildMenu>(GetWorld(), BuildMenuBlueprintClass);
		if (Menu)
		{
			// 获取玩家控制器
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

