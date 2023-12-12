// Fill out your copyright notice in the Description page of Project Settings.


#include "GameHUD.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "TowerDefenceGameModeBase.h"

bool UGameHUD::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}

	//绑定点击事件
	PauseBtn->OnClicked.AddDynamic(this, &UGameHUD::ClickPauseBtn);
	ResumeBtn->OnClicked.AddDynamic(this, &UGameHUD::ClickResumeBtn);
	DoubleSpeedBtn->OnClicked.AddDynamic(this, &UGameHUD::ClickDoubleSpeedBtn);
	RecoverSpeedBtn->OnClicked.AddDynamic(this, &UGameHUD::ClickRecoverSpeedBtn);
	MenuBtn->OnClicked.AddDynamic(this, &UGameHUD::ClickMenuBtn);


	//设定初始按钮
	if (!UGameplayStatics::IsGamePaused(GetWorld()))
	{
		ResumeBtn->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		PauseBtn->SetVisibility(ESlateVisibility::Hidden);
	}

	//隐藏恢复速度的按钮
	RecoverSpeedBtn->SetVisibility(ESlateVisibility::Hidden);
	
	return true;
}

void UGameHUD::ClickPauseBtn()
{
	//暂停游戏
	if (!UGameplayStatics::IsGamePaused(GetWorld()))
	{
		UGameplayStatics::SetGamePaused(GetWorld(), true);
	}

	//更换按钮
	ResumeBtn->SetVisibility(ESlateVisibility::Visible);
	PauseBtn->SetVisibility(ESlateVisibility::Hidden);
}

void UGameHUD::ClickResumeBtn()
{
	//继续游戏
	if (UGameplayStatics::IsGamePaused(GetWorld()))
	{
		UGameplayStatics::SetGamePaused(GetWorld(), false);
	}

	//更换按钮
	ResumeBtn->SetVisibility(ESlateVisibility::Hidden);
	PauseBtn->SetVisibility(ESlateVisibility::Visible);
}

void UGameHUD::ClickDoubleSpeedBtn()
{
	//设置游戏为二倍速
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 2.f);

	//更换按钮
	RecoverSpeedBtn->SetVisibility(ESlateVisibility::Visible);
	DoubleSpeedBtn->SetVisibility(ESlateVisibility::Hidden);
}

void UGameHUD::ClickRecoverSpeedBtn()
{
	//设置游戏为一倍速
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.f);

	//更换按钮
	RecoverSpeedBtn->SetVisibility(ESlateVisibility::Hidden);
	DoubleSpeedBtn->SetVisibility(ESlateVisibility::Visible);
}

void UGameHUD::ClickMenuBtn()
{
	ATowerDefenceGameModeBase* MyGameMode = GetWorld()->GetAuthGameMode<ATowerDefenceGameModeBase>();
	if (MyGameMode)
	{
		MyGameMode->OpenPauseMenu();
	}
}
