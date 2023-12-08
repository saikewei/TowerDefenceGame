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

	//暂停按钮
	UPROPERTY(meta = (BindWidget))
	UButton* PauseBtn;

	UPROPERTY(meta = (BindWidget))
	UButton* ResumeBtn;

	UPROPERTY(meta = (BindWidget))
	UButton* DoubleSpeedBtn;

	UPROPERTY(meta = (BindWidget))
	UButton* RecoverSpeedBtn;

protected:
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
};
