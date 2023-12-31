// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HPBarWidget.generated.h"
/**
 * 
 */
class UProgressBar;
UCLASS()
class TOWERDEFENCEGAME_API UHPBarWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(meta = (BindWidget))
	UProgressBar* Bar;

	UFUNCTION(BlueprintCallable)
	void SetPersent(const float NewPersent);

	UPROPERTY(BlueprintReadWrite)
	float Persentage;
};
