// Fill out your copyright notice in the Description page of Project Settings.


#include "UpgradeCarrotMenu.h"
#include "Carrot.h"

void UUpgradeCarrotMenu::NativeConstruct()
{
	Super::NativeConstruct();
	UE_LOG(LogTemp, Warning, TEXT("Click"));
	UpgradeBtn->OnClicked.AddDynamic(this, &UUpgradeCarrotMenu::OnClickUpgradeBtn);
	UpgradeBtn->SetVisibility(ESlateVisibility::Hidden);

	if (this->TargetCarrot)
	{
		AToweDefenceGameState* GameState = GetWorld()->GetGameState<AToweDefenceGameState>();
		UpgradeBtn->SetVisibility(ESlateVisibility::Visible);
		if (GameState->GetMoney() < 880)
			UpgradeBtn->SetIsEnabled(false);
	}
}

void UUpgradeCarrotMenu::OnClickUpgradeBtn()
{
	UE_LOG(LogTemp, Warning, TEXT("Click"));

	TargetCarrot->UpgradeCarrot();
	this->RemoveFromParent();
}