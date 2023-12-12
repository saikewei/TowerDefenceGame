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
	//��ʼ������
	virtual bool Initialize()override;

	

protected:
	//��ͣ��ť
	UPROPERTY(meta = (BindWidget))
	UButton* PauseBtn;

	//������ť
	UPROPERTY(meta = (BindWidget))
	UButton* ResumeBtn;

	//������
	UPROPERTY(meta = (BindWidget))
	UButton* DoubleSpeedBtn;

	//�ص�һ����
	UPROPERTY(meta = (BindWidget))
	UButton* RecoverSpeedBtn;

	//�˵���ť
	UPROPERTY(meta = (BindWidget))
	UButton* MenuBtn;

	//��ͣ��ť����¼�������
	UFUNCTION()
	void ClickPauseBtn();

	//������ť����¼�������
	UFUNCTION()
	void ClickResumeBtn();

	UFUNCTION()
	void ClickDoubleSpeedBtn();

	UFUNCTION()
	void ClickRecoverSpeedBtn();

	UFUNCTION()
	void ClickMenuBtn();
};
