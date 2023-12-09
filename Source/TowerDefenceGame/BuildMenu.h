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
	//��ʼ������
	virtual void NativeConstruct() override;

	// �Ƿ���ڷ�����
	UPROPERTY(EditAnywhere, Category = "BuildMenu")
	bool HasTower;

	// ����λ��
	UPROPERTY(EditAnywhere, Category = "BuildMenu")
	FVector BuildLocation;

	// ���Ӧ������ָ��
	UPROPERTY(EditAnywhere, Category = "BuildMenu")
	ATowerBase* TargetBase;

	// ����ƿ�����İ�ť
	UPROPERTY(meta = (BindWidget))
	UButton* TBottleBtn;

protected:
	// �������ƿ�����¼�
	UFUNCTION()
	void ClickTBottleBtn();

	// ƿ������ͼ����
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<ATBottle> Bottle;
	
};
