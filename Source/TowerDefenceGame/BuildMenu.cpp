// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildMenu.h"
#include "TowerBase.h"
const int BottleCost = 100;

void UBuildMenu::NativeConstruct()
{
	Super::NativeConstruct();
	// ��ȡGameState
	AToweDefenceGameState* GameState = GetWorld()->GetGameState<AToweDefenceGameState>();
	// �󶨵���¼�
	TBottleBtn->OnClicked.AddDynamic(this, &UBuildMenu::ClickTBottleBtn);
	if (GameState->GetMoney() < BottleCost)
	{
		TBottleBtn->SetIsEnabled(false);
	}
	else
	{
		TBottleBtn->SetIsEnabled(true);
	}
}

void UBuildMenu::ClickTBottleBtn()
{
	AToweDefenceGameState* GameState = GetWorld()->GetGameState<AToweDefenceGameState>();
	UWorld* World = GetWorld();
	FRotator Rotation = FRotator(0, 0, 0);
	Tower = World->SpawnActor<ATBottle>(Bottle, BuildLocation, Rotation);
	UE_LOG(LogTemp, Warning, TEXT("Spawn"));
	this->RemoveFromParent();
	TargetBase->ToggleSignVsibility(false);
	TargetBase->IsPlusSign = false;
	GameState->AddMoney(-BottleCost);
}
