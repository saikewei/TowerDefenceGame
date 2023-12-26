// Fill out your copyright notice in the Description page of Project Settings.


#include "UpgradeSellMenu.h"
#include "TowerPaperFlipbookActor.h"

void UUpgradeSellMenu::NativeConstruct()
{
	Super::NativeConstruct();
	//绑定点击事件
	UpgradeBtnL1->OnClicked.AddDynamic(this, &UUpgradeSellMenu::OnClickUpgradeBtnL1);
	UpgradeBtnL2->OnClicked.AddDynamic(this, &UUpgradeSellMenu::OnClickUpgradeBtnL2);
	SellBtnL1->OnClicked.AddDynamic(this, &UUpgradeSellMenu::OnClickSellBtnL1);
	SellBtnL2->OnClicked.AddDynamic(this, &UUpgradeSellMenu::OnClickSellBtnL2);
	SellBtnL3->OnClicked.AddDynamic(this, &UUpgradeSellMenu::OnClickSellBtnL3);
	//初始全设为不可见
	UpgradeBtnL1->SetVisibility(ESlateVisibility::Hidden);
	UpgradeBtnL2->SetVisibility(ESlateVisibility::Hidden);
	UpgradeBtnL3->SetVisibility(ESlateVisibility::Hidden);
	SellBtnL1->SetVisibility(ESlateVisibility::Hidden);
	SellBtnL2->SetVisibility(ESlateVisibility::Hidden);
	SellBtnL3->SetVisibility(ESlateVisibility::Hidden);
	if (this->TargetTower)
	{
		AToweDefenceGameState* GameState = GetWorld()->GetGameState<AToweDefenceGameState>();
		switch (TargetTower->CurrentLevel)
		{
			case 0:
				UpgradeBtnL1->SetVisibility(ESlateVisibility::Visible);
				SellBtnL1->SetVisibility(ESlateVisibility::Visible);
				UE_LOG(LogTemp, Warning, TEXT("Set"));
				if (GameState->GetMoney() < TargetTower->UpgradeCost[0])
				{
					UpgradeBtnL1->SetIsEnabled(false);
				}
				break;
			case 1:
				UpgradeBtnL2->SetVisibility(ESlateVisibility::Visible);
				SellBtnL2->SetVisibility(ESlateVisibility::Visible);
				if (GameState->GetMoney() < TargetTower->UpgradeCost[1])
				{
					UpgradeBtnL2->SetIsEnabled(false);
				}
				break;
			case 2:
				UpgradeBtnL3->SetVisibility(ESlateVisibility::Visible);
				SellBtnL3->SetVisibility(ESlateVisibility::Visible);
				UpgradeBtnL3->SetIsEnabled(false);
				break;
		}
	}
	//UE_LOG(LogTemp, Warning, TEXT("Construct"));
}

void UUpgradeSellMenu::OnClickUpgradeBtnL1()
{
	TargetTower->UpgradeTower();
	this->RemoveFromParent();
}

void UUpgradeSellMenu::OnClickUpgradeBtnL2()
{
	TargetTower->UpgradeTower();
	this->RemoveFromParent();
}

void UUpgradeSellMenu::OnClickSellBtnL1()
{
	TargetTower->SellTower();
	TargetTower = nullptr;
	this->RemoveFromParent();
}

void UUpgradeSellMenu::OnClickSellBtnL2()
{
	TargetTower->SellTower();
	TargetTower = nullptr;
	this->RemoveFromParent();
}

void UUpgradeSellMenu::OnClickSellBtnL3()
{
	TargetTower->SellTower();
	TargetTower = nullptr;
	this->RemoveFromParent();
}


