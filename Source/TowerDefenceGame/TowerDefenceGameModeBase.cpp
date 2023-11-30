// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerDefenceGameModeBase.h"
#include "Kismet/GameplayStatics.h"

void ATowerDefenceGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	
	//查找处理本地玩家控制的Actor
	APlayerController* MyPlayerController = UGameplayStatics::GetPlayerController(this, 0);
	if (MyPlayerController)
	{
		//释放鼠标光标
		MyPlayerController->SetShowMouseCursor(true);
	}
}
