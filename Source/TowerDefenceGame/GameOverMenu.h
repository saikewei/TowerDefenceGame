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
	// ��ʼ������
	virtual void NativeConstruct() override;
	
protected:
	//�ؿ���ť
	UPROPERTY(meta = (BindWidget))
	UButton* RestartBtn;

	//�˳���ť
	UPROPERTY(meta = (BindWidget))
	UButton* ExitBtn;

	//����¼�������
	UFUNCTION()
	virtual void ClickRestartBtn();

	UFUNCTION()
	void ClickExitBtn();

	//���˵��ؿ�������
	UPROPERTY(EditAnyWhere)
	FName NameOfMainLevel;

	void SaveCurrentGame();
};
