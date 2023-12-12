// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameHUD.generated.h"

/**
 * 
 */
class UButton;

UCLASS()
class TOWERDEFENCEGAME_API UGameHUD : public UUserWidget
{
	GENERATED_BODY()

public:
	//初始化函数
	virtual bool Initialize()override;

	

protected:
	//暂停按钮
	UPROPERTY(meta = (BindWidget))
	UButton* PauseBtn;

	//继续按钮
	UPROPERTY(meta = (BindWidget))
	UButton* ResumeBtn;

	//二倍速
	UPROPERTY(meta = (BindWidget))
	UButton* DoubleSpeedBtn;

	//回到一倍速
	UPROPERTY(meta = (BindWidget))
	UButton* RecoverSpeedBtn;

	//菜单按钮
	UPROPERTY(meta = (BindWidget))
	UButton* MenuBtn;

	//暂停按钮点击事件处理函数
	UFUNCTION()
	void ClickPauseBtn();

	//继续按钮点击事件处理函数
	UFUNCTION()
	void ClickResumeBtn();

	UFUNCTION()
	void ClickDoubleSpeedBtn();

	UFUNCTION()
	void ClickRecoverSpeedBtn();

	UFUNCTION()
	void ClickMenuBtn();
};
