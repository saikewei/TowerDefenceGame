// Fill out your copyright notice in the Description page of Project Settings.


#include "Carrot.h"
#include "TowerDefenceGameModeBase.h"

// Sets default values
ACarrot::ACarrot()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	//设置血量默认值
	CarrotHealth = 100.0f;

	Carrot_1 = LoadObject<UPaperFlipbook>(nullptr, TEXT("/Script/Paper2D.PaperFlipbook'/Game/GuardCarrot/Flipbooks/carrot_1.carrot_1'"));
	Carrot_2 = LoadObject<UPaperFlipbook>(nullptr, TEXT("/Script/Paper2D.PaperFlipbook'/Game/GuardCarrot/Flipbooks/carrot_2.carrot_2'"));
	Carrot_3 = LoadObject<UPaperFlipbook>(nullptr, TEXT("/Script/Paper2D.PaperFlipbook'/Game/GuardCarrot/Flipbooks/carrot_3.carrot_3'"));
	Carrot_4 = LoadObject<UPaperFlipbook>(nullptr, TEXT("/Script/Paper2D.PaperFlipbook'/Game/GuardCarrot/Flipbooks/carrot_4.carrot_4'"));
	Carrot_5 = LoadObject<UPaperFlipbook>(nullptr, TEXT("/Script/Paper2D.PaperFlipbook'/Game/GuardCarrot/Flipbooks/carrot_5.carrot_5'"));
	FlipbookComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("FlipbookComponent"));
	FlipbookComponent->SetupAttachment(RootComponent);
	SetRootComponent(FlipbookComponent);

	FlipbookComponent->SetFlipbook(Carrot_1);
}

// Called when the game starts or when spawned
void ACarrot::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ACarrot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACarrot::UpdateFlipbook()
{
	UPaperFlipbook* NewFlipbook = nullptr;
	if (FlipbookComponent)
	{
		if (CarrotHealth > 80.0f)
			NewFlipbook = Carrot_1;
		// Set flipbook for high health
		else if (CarrotHealth > 60.0f)
			NewFlipbook = Carrot_2;
		// Set flipbook for moderate health
		else if (CarrotHealth > 40.0f)
			NewFlipbook = Carrot_3;
		// Set flipbook for low health
		else if (CarrotHealth > 20.0f)
			NewFlipbook = Carrot_4;
		else
			NewFlipbook = Carrot_5;
	}
	FlipbookComponent->SetFlipbook(NewFlipbook);
}


//获得给萝卜的伤害
void ACarrot::GetDamage(float Damage)
{
	CarrotHealth -= Damage;
	UpdateFlipbook(); // 更新萝卜图像
	if (CarrotHealth < 0)
	{
		CarrotHealth = 0;
		GetWorld()->GetAuthGameMode<ATowerDefenceGameModeBase>()->GameLost();
	}
}

void ACarrot::MyTakeDamage(float DamageAmount)
{
	// 减血
	CarrotHealth -= DamageAmount;
	if (CarrotHealth <= 0.0f)
	{
		Destroy();
	}
}