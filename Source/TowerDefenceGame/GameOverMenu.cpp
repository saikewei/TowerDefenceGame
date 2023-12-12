// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOverMenu.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UGameOverMenu::NativeConstruct()
{
	Super::NativeConstruct();
	//绑定点击事件
	RestartBtn->OnClicked.AddDynamic(this, &UGameOverMenu::ClickRestartBtn);
	ExitBtn->OnClicked.AddDynamic(this, &UGameOverMenu::ClickExitBtn);

	//更改输入模式使得玩家只能操控菜单
	GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeUIOnly().SetWidgetToFocus(TakeWidget()));
}

void UGameOverMenu::ClickRestartBtn()
{
	//重新打开当前关卡
	UGameplayStatics::OpenLevel(GetWorld(), FName(UGameplayStatics::GetCurrentLevelName(GetWorld())));
}

void UGameOverMenu::ClickExitBtn()
{
	//回到主菜单
	UGameplayStatics::OpenLevel(GetWorld(), NameOfMainLevel);
}
