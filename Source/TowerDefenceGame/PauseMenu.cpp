// Fill out your copyright notice in the Description page of Project Settings.


#include "PauseMenu.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "TowerDefenceGameModeBase.h"

void UPauseMenu::NativeConstruct()
{
	Super::NativeConstruct();

	//�󶨵���¼�
	if (ResumeBtn)
	{
		ResumeBtn->OnClicked.RemoveDynamic(this, &UPauseMenu::ClickResumeBtn);
		ResumeBtn->OnClicked.AddDynamic(this, &UPauseMenu::ClickResumeBtn);
	}

	if (RestartBtn)
	{
		RestartBtn->OnClicked.RemoveDynamic(this, &UPauseMenu::ClickRestartBtn);
		RestartBtn->OnClicked.AddDynamic(this, &UPauseMenu::ClickRestartBtn);
	}

	if (ExitBtn)
	{
		ExitBtn->OnClicked.RemoveDynamic(this, &UPauseMenu::ClickExitBtn);
		ExitBtn->OnClicked.AddDynamic(this, &UPauseMenu::ClickExitBtn);
	}

	//��ȡ��ǰ��Ϸ��ͣ״̬
	IsGamePausedBefore = UGameplayStatics::IsGamePaused(GetWorld());

	//û��ͣ����ͣ��Ϸ
	if (!IsGamePausedBefore) 
	{
		UGameplayStatics::SetGamePaused(GetWorld(), true);
	}

	//��������ģʽʹ�����ֻ�ܲٿز˵�
	GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeUIOnly().SetWidgetToFocus(TakeWidget()));
}

void UPauseMenu::ClickResumeBtn()
{
	//�����ǰ��Ϸû����ͣ����ָ���Ϸ
	if (!IsGamePausedBefore)
	{
		UGameplayStatics::SetGamePaused(GetWorld(), false);
	}

	//�ָ�����ģʽ
	GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeGameAndUI().SetHideCursorDuringCapture(false));

	//�رղ˵�
	this->RemoveFromParent();
}

void UPauseMenu::ClickRestartBtn()
{
	UGameplayStatics::OpenLevel(GetWorld(), FName(UGameplayStatics::GetCurrentLevelName(GetWorld())));
	//���´򿪵�ǰ�ؿ�
	//UE_LOG(LogTemp, Warning, TEXT("%s"), *FString(UGameplayStatics::GetCurrentLevelName(GetWorld())));
	//UGameplayStatics::OpenLevel(GetWorld(), FName(UGameplayStatics::GetCurrentLevelName(GetWorld())));
}

void UPauseMenu::ClickExitBtn()
{
	//�ص����˵�
	UGameplayStatics::OpenLevel(GetWorld(), FName(FString("MenuLevel")));
}
