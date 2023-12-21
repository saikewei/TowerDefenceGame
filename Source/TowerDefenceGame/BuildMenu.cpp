// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildMenu.h"
#include "TowerBase.h"
const int BottleCost = 100;
const int ShitCost = 120;
const int FanCost = 160;

void UBuildMenu::NativeConstruct()
{
	Super::NativeConstruct();
	// ��ȡGameState
	AToweDefenceGameState* GameState = GetWorld()->GetGameState<AToweDefenceGameState>();
	// �󶨵���¼�
	TBottleBtn->OnClicked.AddDynamic(this, &UBuildMenu::ClickTBottleBtn);
	TShitBtn->OnClicked.AddDynamic(this, &UBuildMenu::ClickTShitBtn);
	TFanBtn->OnClicked.AddDynamic(this, &UBuildMenu::ClickTFanBtn);
	//���ð�ť�Ƿ�ɵ��
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
	if (GameState->GetMoney() < FanCost)
	{
		TFanBtn->SetIsEnabled(false);
	}
	else
	{
		TFanBtn->SetIsEnabled(true);
	}

}

void UBuildMenu::ClickTBottleBtn()
{
	AToweDefenceGameState* GameState = GetWorld()->GetGameState<AToweDefenceGameState>();
	UWorld* World = GetWorld();
	FRotator Rotation = FRotator(0, 0, 0);
	Tower = World->SpawnActor<ATBottle>(Bottle, BuildLocation, Rotation);
	Tower->SetMyBase(TargetBase);
	//UE_LOG(LogTemp, Warning, TEXT("Spawn"));
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
	//UE_LOG(LogTemp, Warning, TEXT("Spawn"));
	this->RemoveFromParent();
	TargetBase->ToggleSignVsibility(false);
	TargetBase->IsPlusSign = false;
	GameState->AddMoney(-ShitCost);
}

void UBuildMenu::ClickTFanBtn()
{
	AToweDefenceGameState* GameState = GetWorld()->GetGameState<AToweDefenceGameState>();
	UWorld* World = GetWorld();
	FRotator Rotation = FRotator(0, 0, 0);
	Tower = World->SpawnActor<ATFan>(Fan, BuildLocation, Rotation);
	Tower->SetMyBase(TargetBase);
	//UE_LOG(LogTemp, Warning, TEXT("Spawn"));
	this->RemoveFromParent();
	TargetBase->ToggleSignVsibility(false);
	TargetBase->IsPlusSign = false;
	GameState->AddMoney(-FanCost);
}
