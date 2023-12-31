// Fill out your copyright notice in the Description page of Project Settings.


#include "ObstaclePaperFlipbookActor.h"
#include "Components/BoxComponent.h"


AObstaclePaperFlipbookActor::AObstaclePaperFlipbookActor()
{
	
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//��ײԤ��Ϊ�����ӵ���ѡ�к�Ž����ӵ�
	CollisionBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldDynamic, ECollisionResponse::ECR_Ignore);
}

void AObstaclePaperFlipbookActor::BeginPlay()
{
    Super::BeginPlay();

    //��ʼ������ϰ���Ѫ������
    SetHPBarMarkVisibility(false);
}

void AObstaclePaperFlipbookActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (HP != MAX_HP)
    {
        //�ϰ����Ѫ����ʾѪ��
        SetHPBarMarkVisibility(true);
    }
}

void AObstaclePaperFlipbookActor::ToggleCollision(bool Aimed)
{
    UE_LOG(LogTemp, Warning, TEXT("Change to %d"), Aimed);
    if (Aimed)
    {
        // ���ϰ��ﱻѡ��ʱ���������ӵ������ص�
        CollisionBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldDynamic, ECollisionResponse::ECR_Overlap);
    }
    else
    {
        // ���ϰ���δ��ѡ��ʱ�������ӵ�
        CollisionBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldDynamic, ECollisionResponse::ECR_Ignore);
    }
}

void AObstaclePaperFlipbookActor::Die()
{
    Destroy();
}
