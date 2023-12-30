// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "Blueprint/UserWidget.h"
#include "UpgradeCarrotMenu.generated.h"


/**
 *
 */
class UButton;
class ACarrot;
UCLASS()
class TOWERDEFENCEGAME_API UUpgradeCarrotMenu :public UUserWidget
{
	GENERATED_BODY()
	friend class ACarrot;
public:
	virtual void NativeConstruct() override;
protected:
	UFUNCTION()
		void OnClickUpgradeBtn();
	UPROPERTY(meta = (BindWidget))
		UButton* UpgradeBtn;
	UPROPERTY(EditAnywhere, Category = "Menu")
		ACarrot* TargetCarrot;
	UPROPERTY(EditAnywhere, Category = "Menu")
		FVector BuildLocation;
};
