// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PauseMenu.generated.h"

class UButton;
/**
 * 
 */
UCLASS()
class TOWERDEFENCEGAME_API UPauseMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	// 初始化函数
	virtual void NativeConstruct() override;

protected:
	//继续按钮
	UPROPERTY(meta = (BindWidget))
	UButton* ResumeBtn;

	//重开按钮
	UPROPERTY(meta = (BindWidget))
	UButton* RestartBtn;

	//退出按钮
	UPROPERTY(meta = (BindWidget))
	UButton* ExitBtn;

	//点击事件处理函数

	UFUNCTION()
	void ClickResumeBtn();

	UFUNCTION()
	void ClickRestartBtn();

	UFUNCTION()
	void ClickExitBtn();

	//在打开菜单前游戏是否已经暂停
	bool IsGamePausedBefore;

	//主菜单关卡的名字
	UPROPERTY(EditAnyWhere)
	FName NameOfMainLevel;
};
