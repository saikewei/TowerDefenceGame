// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOverMenu.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "ToweDefenceGameState.h"
#include "TowerDefenceSaveGame.h"

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
	UGameplayStatics::OpenLevel(GetWorld(), FName(FString("MenuLevel")));
}

void UGameOverMenu::SaveCurrentGame()
{
	UTowerDefenceSaveGame* SaveGameInstance = Cast<UTowerDefenceSaveGame>(UGameplayStatics::CreateSaveGameObject(UTowerDefenceSaveGame::StaticClass()));
	
	SaveGameInstance->EnableLevel2();

	SaveGameInstance->num = 9;

	bool isSuccess = UGameplayStatics::SaveGameToSlot(SaveGameInstance, TEXT("slot7"), 1);

	UE_LOG(LogTemp, Warning, TEXT("save success!Result:%d"), isSuccess);
}
