// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "Blueprint/UserWidget.h"
#include "UpgradeSellMenu.generated.h"

/**
 * 
 */
class UButton;
class ATowerPaperFlipbookActor;

UCLASS()
class TOWERDEFENCEGAME_API UUpgradeSellMenu : public UUserWidget
{
	GENERATED_BODY()
	friend class ATowerPaperFlipbookActor;
public:
	//初始化函数
	virtual void NativeConstruct() override;

protected:
	// 点击升级事件
	UFUNCTION()
	void OnClickUpgradeBtnL1();

	UFUNCTION()
	void OnClickUpgradeBtnL2();

	// 点击售出事件
	UFUNCTION()
	void OnClickSellBtnL1();

	UFUNCTION()
	void OnClickSellBtnL2();

	UFUNCTION()
	void OnClickSellBtnL3();

	//升级按钮
	UPROPERTY(meta = (BindWidget))
	UButton* UpgradeBtnL1;

	UPROPERTY(meta = (BindWidget))
	UButton* UpgradeBtnL2;

	UPROPERTY(meta = (BindWidget))
	UButton* UpgradeBtnL3;

	//售出按钮
	UPROPERTY(meta = (BindWidget))
	UButton* SellBtnL1;

	UPROPERTY(meta = (BindWidget))
	UButton* SellBtnL2;

	UPROPERTY(meta = (BindWidget))
	UButton* SellBtnL3;

	//其对应防御塔的指针
	UPROPERTY(EditAnywhere, Category = "Menu")
	ATowerPaperFlipbookActor* TargetTower;

	//生成位置
	UPROPERTY(EditAnywhere, Category = "Menu")
	FVector BuildLocation;

};
