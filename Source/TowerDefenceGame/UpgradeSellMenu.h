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
	// ��ʼ������
	virtual void NativeConstruct() override;

	// ������ť
	UPROPERTY(meta = (BindWidget))
	UButton* UpgradeBtn;

	// �۳���ť
	UPROPERTY(meta = (BindWidget))
	UButton* SellBtn;

	// ���Ӧ������ָ��
	UPROPERTY(EditAnywhere, Category = "Menu")
	ATowerPaperFlipbookActor* TargetTower;

protected:
	// ��������¼�
	UFUNCTION()
	void OnClickUpgradeBtn();

	// ����۳��¼�
	void OnClickSellBtn();
};
