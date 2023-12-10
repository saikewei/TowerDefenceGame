// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "TowerPaperFlipbookActor.h"
#include "TBottle.h"
#include "ToweDefenceGameState.h"
#include "BuildMenu.generated.h"

/**
 * 
 */
class UButton;
class ATowerBase;
class ATowerPaperFlipbookActor;

UCLASS()
class TOWERDEFENCEGAME_API UBuildMenu : public UUserWidget
{
	GENERATED_BODY()
public:
	//初始化函数
	virtual void NativeConstruct() override;

	// 生成位置
	UPROPERTY(EditAnywhere, Category = "BuildMenu")
	FVector BuildLocation;

	// 其对应塔基的指针
	UPROPERTY(EditAnywhere, Category = "BuildMenu")
	ATowerBase* TargetBase;

	//指向防御塔的指针
	UPROPERTY(EditAnywhere, Category = "BuildMenu")
	ATowerPaperFlipbookActor* Tower;

	// 建造瓶子塔的按钮
	UPROPERTY(meta = (BindWidget))
	UButton* TBottleBtn;

protected:
	// 点击建造瓶子塔事件
	UFUNCTION()
	void ClickTBottleBtn();

	// 瓶子塔蓝图子类
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<ATBottle> Bottle;
	
};
