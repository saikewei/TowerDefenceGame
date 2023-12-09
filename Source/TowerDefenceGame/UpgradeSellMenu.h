// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "Blueprint/UserWidget.h"
#include "TowerPaperFlipbookActor.h"
#include "UpgradeSellMenu.generated.h"

/**
 * 
 */
class UButton;

UCLASS()
class TOWERDEFENCEGAME_API UUpgradeSellMenu : public UUserWidget
{
	GENERATED_BODY()
public:
	// 初始化函数
	virtual void NativeConstruct() override;

	// 升级按钮
	UPROPERTY(meta = (BindWidget))
	UButton* UpgradeBtn;

	// 售出按钮
	UPROPERTY(meta = (BindWidget))
	UButton* SellBtn;

	// 其对应塔基的指针
	UPROPERTY(EditAnywhere, Category = "Menu")
	ATowerPaperFlipbookActor* TargetTower;

protected:
	// 点击升级事件
	UFUNCTION()
	void OnClickUpgradeBtn();

	// 点击售出事件
	void OnClickSellBtn();
};
