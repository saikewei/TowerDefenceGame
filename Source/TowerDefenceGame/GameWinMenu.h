// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameOverMenu.h"
#include "GameWinMenu.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENCEGAME_API UGameWinMenu : public UGameOverMenu
{
	GENERATED_BODY()
public:
	// ³õÊ¼»¯º¯Êý
	virtual void NativeConstruct() override;

protected:
	virtual void ClickRestartBtn();
};
