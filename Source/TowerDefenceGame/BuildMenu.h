// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "TowerPaperFlipbookActor.h"
#include "TBottle.h"
#include "TShit.h"
#include "TFan.h"
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
	//��ʼ������
	virtual void NativeConstruct() override;

	// ����λ��
	UPROPERTY(EditAnywhere, Category = "BuildMenu")
	FVector BuildLocation;

	// ���Ӧ������ָ��
	UPROPERTY(EditAnywhere, Category = "BuildMenu")
	ATowerBase* TargetBase;

	//ָ���������ָ��
	UPROPERTY(EditAnywhere, Category = "BuildMenu")
	ATowerPaperFlipbookActor* Tower;

	//����ƿ�����İ�ť
	UPROPERTY(meta = (BindWidget))
	UButton* TBottleBtn;

	//���������İ�ť
	UPROPERTY(meta = (BindWidget))
	UButton* TShitBtn;

	//����������İ�ť
	UPROPERTY(meta = (BindWidget))
	UButton* TFanBtn;

protected:
	//�������ƿ�����¼�
	UFUNCTION()
	void ClickTBottleBtn();

	//ƿ������ͼ����
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<ATBottle> Bottle;

	//������������¼�
	UFUNCTION()
	void ClickTShitBtn();

	//�������ͼ����
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<ATShit> Shit;
	
	//�������������¼�
	UFUNCTION()
	void ClickTFanBtn();

	//��������ͼ����
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<ATFan> Fan;

};
