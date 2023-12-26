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
	//��ʼ������
	virtual void NativeConstruct() override;

protected:
	// ��������¼�
	UFUNCTION()
	void OnClickUpgradeBtnL1();

	UFUNCTION()
	void OnClickUpgradeBtnL2();

	// ����۳��¼�
	UFUNCTION()
	void OnClickSellBtnL1();

	UFUNCTION()
	void OnClickSellBtnL2();

	UFUNCTION()
	void OnClickSellBtnL3();

	//������ť
	UPROPERTY(meta = (BindWidget))
	UButton* UpgradeBtnL1;

	UPROPERTY(meta = (BindWidget))
	UButton* UpgradeBtnL2;

	UPROPERTY(meta = (BindWidget))
	UButton* UpgradeBtnL3;

	//�۳���ť
	UPROPERTY(meta = (BindWidget))
	UButton* SellBtnL1;

	UPROPERTY(meta = (BindWidget))
	UButton* SellBtnL2;

	UPROPERTY(meta = (BindWidget))
	UButton* SellBtnL3;

	//���Ӧ��������ָ��
	UPROPERTY(EditAnywhere, Category = "Menu")
	ATowerPaperFlipbookActor* TargetTower;

	//����λ��
	UPROPERTY(EditAnywhere, Category = "Menu")
	FVector BuildLocation;

};
