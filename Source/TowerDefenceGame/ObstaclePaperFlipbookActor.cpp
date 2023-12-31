// Fill out your copyright notice in the Description page of Project Settings.


#include "ObstaclePaperFlipbookActor.h"
#include "Components/BoxComponent.h"


AObstaclePaperFlipbookActor::AObstaclePaperFlipbookActor()
{
	
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//碰撞预设为忽略子弹，选中后才接受子弹
	CollisionBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldDynamic, ECollisionResponse::ECR_Ignore);
}

void AObstaclePaperFlipbookActor::BeginPlay()
{
    Super::BeginPlay();

    //初始情况下障碍物血条隐藏
    SetHPBarMarkVisibility(false);
}

void AObstaclePaperFlipbookActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (HP != MAX_HP)
    {
        //障碍物掉血就显示血条
        SetHPBarMarkVisibility(true);
    }
}

void AObstaclePaperFlipbookActor::ToggleCollision(bool Aimed)
{
    UE_LOG(LogTemp, Warning, TEXT("Change to %d"), Aimed);
    if (Aimed)
    {
        // 当障碍物被选中时，允许与子弹发生重叠
        CollisionBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldDynamic, ECollisionResponse::ECR_Overlap);
    }
    else
    {
        // 当障碍物未被选中时，忽略子弹
        CollisionBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldDynamic, ECollisionResponse::ECR_Ignore);
    }
}

void AObstaclePaperFlipbookActor::Die()
{
    Destroy();
}
