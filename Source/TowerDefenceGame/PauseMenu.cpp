// Fill out your copyright notice in the Description page of Project Settings.


#include "PauseMenu.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "TowerDefenceGameModeBase.h"

void UPauseMenu::NativeConstruct()
{
	Super::NativeConstruct();

	//绑定点击事件
	ResumeBtn->OnClicked.AddDynamic(this, &UPauseMenu::ClickResumeBtn);
	RestartBtn->OnClicked.AddDynamic(this, &UPauseMenu::ClickRestartBtn);
	ExitBtn->OnClicked.AddDynamic(this, &UPauseMenu::ClickExitBtn);

	//获取当前游戏暂停状态
	IsGamePausedBefore = UGameplayStatics::IsGamePaused(GetWorld());

	//没暂停就暂停游戏
	if (!IsGamePausedBefore) 
	{
		UGameplayStatics::SetGamePaused(GetWorld(), true);
	}

	//更改输入模式使得玩家只能操控菜单
	GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeUIOnly().SetWidgetToFocus(TakeWidget()));
}

void UPauseMenu::ClickResumeBtn()
{
	//如果此前游戏没有暂停，则恢复游戏
	if (!IsGamePausedBefore)
	{
		UGameplayStatics::SetGamePaused(GetWorld(), false);
	}

	//恢复输入模式
	GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeGameAndUI().SetHideCursorDuringCapture(false));

	//关闭菜单
	this->RemoveFromParent();
}

void UPauseMenu::ClickRestartBtn()
{
	UGameplayStatics::OpenLevel(GetWorld(), FName(FString("level2")));
	//重新打开当前关卡
	//UE_LOG(LogTemp, Warning, TEXT("%s"), *FString(UGameplayStatics::GetCurrentLevelName(GetWorld())));
	//UGameplayStatics::OpenLevel(GetWorld(), FName(UGameplayStatics::GetCurrentLevelName(GetWorld())));
}

void UPauseMenu::ClickExitBtn()
{
	//回到主菜单
	UGameplayStatics::OpenLevel(GetWorld(), FName(FString("MenuLevel")));
}
