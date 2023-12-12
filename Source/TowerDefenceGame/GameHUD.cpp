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

	//�󶨵���¼�
	PauseBtn->OnClicked.AddDynamic(this, &UGameHUD::ClickPauseBtn);
	ResumeBtn->OnClicked.AddDynamic(this, &UGameHUD::ClickResumeBtn);
	DoubleSpeedBtn->OnClicked.AddDynamic(this, &UGameHUD::ClickDoubleSpeedBtn);
	RecoverSpeedBtn->OnClicked.AddDynamic(this, &UGameHUD::ClickRecoverSpeedBtn);
	MenuBtn->OnClicked.AddDynamic(this, &UGameHUD::ClickMenuBtn);


	//�趨��ʼ��ť
	if (!UGameplayStatics::IsGamePaused(GetWorld()))
	{
		ResumeBtn->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		PauseBtn->SetVisibility(ESlateVisibility::Hidden);
	}

	//���ػָ��ٶȵİ�ť
	RecoverSpeedBtn->SetVisibility(ESlateVisibility::Hidden);
	
	return true;
}

void UGameHUD::ClickPauseBtn()
{
	//��ͣ��Ϸ
	if (!UGameplayStatics::IsGamePaused(GetWorld()))
	{
		UGameplayStatics::SetGamePaused(GetWorld(), true);
	}

	//������ť
	ResumeBtn->SetVisibility(ESlateVisibility::Visible);
	PauseBtn->SetVisibility(ESlateVisibility::Hidden);
}

void UGameHUD::ClickResumeBtn()
{
	//������Ϸ
	if (UGameplayStatics::IsGamePaused(GetWorld()))
	{
		UGameplayStatics::SetGamePaused(GetWorld(), false);
	}

	//������ť
	ResumeBtn->SetVisibility(ESlateVisibility::Hidden);
	PauseBtn->SetVisibility(ESlateVisibility::Visible);
}

void UGameHUD::ClickDoubleSpeedBtn()
{
	//������ϷΪ������
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 2.f);

	//������ť
	RecoverSpeedBtn->SetVisibility(ESlateVisibility::Visible);
	DoubleSpeedBtn->SetVisibility(ESlateVisibility::Hidden);
}

void UGameHUD::ClickRecoverSpeedBtn()
{
	//������ϷΪһ����
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.f);

	//������ť
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
