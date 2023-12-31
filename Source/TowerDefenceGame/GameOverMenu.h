// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameOverMenu.generated.h"

class UButton;

/**
 * 
 */
UCLASS()
class TOWERDEFENCEGAME_API UGameOverMenu : public UUserWidget
{
	GENERATED_BODY()
public:
	// 初始化函数
	virtual void NativeConstruct() override;
	
protected:
	//重开按钮
	UPROPERTY(meta = (BindWidget))
	UButton* RestartBtn;

	//退出按钮
	UPROPERTY(meta = (BindWidget))
	UButton* ExitBtn;

	//点击事件处理函数
	UFUNCTION()
	virtual void ClickRestartBtn();

	UFUNCTION()
	void ClickExitBtn();

	//主菜单关卡的名字
	UPROPERTY(EditAnyWhere)
	FName NameOfMainLevel;

	void SaveCurrentGame();
};
