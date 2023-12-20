// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildMenu.h"
#include "TowerBase.h"
const int BottleCost = 100;
const int ShitCost = 120;

void UBuildMenu::NativeConstruct()
{
	Super::NativeConstruct();
	// 获取GameState
	AToweDefenceGameState* GameState = GetWorld()->GetGameState<AToweDefenceGameState>();
	// 绑定点击事件
	TBottleBtn->OnClicked.AddDynamic(this, &UBuildMenu::ClickTBottleBtn);
	TShitBtn->OnClicked.AddDynamic(this, &UBuildMenu::ClickTShitBtn);
	//设置按钮是否可点击
	if (GameState->GetMoney() < BottleCost)
	{
		TBottleBtn->SetIsEnabled(false);
	}
	else
	{
		TBottleBtn->SetIsEnabled(true);
	}
	if (GameState->GetMoney() < ShitCost)
	{
		TShitBtn->SetIsEnabled(false);
	}
	else
	{
		TShitBtn->SetIsEnabled(true);
	}


}

void UBuildMenu::ClickTBottleBtn()
{
	AToweDefenceGameState* GameState = GetWorld()->GetGameState<AToweDefenceGameState>();
	UWorld* World = GetWorld();
	FRotator Rotation = FRotator(0, 0, 0);
	Tower = World->SpawnActor<ATBottle>(Bottle, BuildLocation, Rotation);
	Tower->SetMyBase(TargetBase);
	UE_LOG(LogTemp, Warning, TEXT("Spawn"));
	this->RemoveFromParent();
	TargetBase->ToggleSignVsibility(false);
	TargetBase->IsPlusSign = false;
	GameState->AddMoney(-BottleCost);
}

void UBuildMenu::ClickTShitBtn()
{
	AToweDefenceGameState* GameState = GetWorld()->GetGameState<AToweDefenceGameState>();
	UWorld* World = GetWorld();
	FRotator Rotation = FRotator(0, 0, 0);
	Tower = World->SpawnActor<ATShit>(Shit, BuildLocation, Rotation);
	Tower->SetMyBase(TargetBase);
	UE_LOG(LogTemp, Warning, TEXT("Spawn"));
	this->RemoveFromParent();
	TargetBase->ToggleSignVsibility(false);
	TargetBase->IsPlusSign = false;
	GameState->AddMoney(-ShitCost);
}
