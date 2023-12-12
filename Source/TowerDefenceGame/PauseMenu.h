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
	// ��ʼ������
	virtual void NativeConstruct() override;

protected:
	//������ť
	UPROPERTY(meta = (BindWidget))
	UButton* ResumeBtn;

	//�ؿ���ť
	UPROPERTY(meta = (BindWidget))
	UButton* RestartBtn;

	//�˳���ť
	UPROPERTY(meta = (BindWidget))
	UButton* ExitBtn;

	//����¼�������

	UFUNCTION()
	void ClickResumeBtn();

	UFUNCTION()
	void ClickRestartBtn();

	UFUNCTION()
	void ClickExitBtn();

	//�ڴ򿪲˵�ǰ��Ϸ�Ƿ��Ѿ���ͣ
	bool IsGamePausedBefore;

	//���˵��ؿ�������
	UPROPERTY(EditAnyWhere)
	FName NameOfMainLevel;
};
