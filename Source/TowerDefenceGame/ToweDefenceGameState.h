// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "ToweDefenceGameState.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENCEGAME_API AToweDefenceGameState : public AGameStateBase
{
	GENERATED_BODY()
public:
	//��õ�ǰ��Ǯ
	UFUNCTION(BlueprintCallable)
	int32 GetMoney()const;

	//��ӽ�Ǯ����ֵΪ���٣�,��Ǯ��ӳɹ��򷵻���
	UFUNCTION(BlueprintCallable)
	bool AddMoney(int32 MoneyToAdd);
	
protected:
	//��Ǯ��
	UPROPERTY(EditAnywhere)
	int32 Money;
};
