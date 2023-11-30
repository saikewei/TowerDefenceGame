// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerDefenceGameModeBase.h"
#include "Kismet/GameplayStatics.h"

void ATowerDefenceGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	
	//���Ҵ�������ҿ��Ƶ�Actor
	APlayerController* MyPlayerController = UGameplayStatics::GetPlayerController(this, 0);
	if (MyPlayerController)
	{
		//�ͷ������
		MyPlayerController->SetShowMouseCursor(true);
	}
}
