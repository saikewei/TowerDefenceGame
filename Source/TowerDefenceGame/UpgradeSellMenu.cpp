// Fill out your copyright notice in the Description page of Project Settings.


#include "UpgradeSellMenu.h"

void UUpgradeSellMenu::NativeConstruct()
{
	Super::NativeConstruct();
	// �󶨵���¼�
	UpgradeBtn->OnClicked.AddDynamic(this, &UUpgradeSellMenu::OnClickUpgradeBtn);
	SellBtn->OnClicked.AddDynamic(this, &UUpgradeSellMenu::OnClickSellBtn);

}

void UUpgradeSellMenu::OnClickUpgradeBtn()
{

}

void UUpgradeSellMenu::OnClickSellBtn()
{

}
