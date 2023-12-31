// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "ToweDefenceGameState.generated.h"

class AMonsterPaperFlipbookActor;

/**
 * 
 */
UCLASS()
class TOWERDEFENCEGAME_API AToweDefenceGameState : public AGameStateBase
{
	GENERATED_BODY()
public:
	AToweDefenceGameState();

	//��õ�ǰ��Ǯ
	UFUNCTION(BlueprintCallable)
	int32 GetMoney()const;

	//��ӽ�Ǯ����ֵΪ���٣�,��Ǯ��ӳɹ��򷵻���
	UFUNCTION(BlueprintCallable)
	bool AddMoney(int32 MoneyToAdd);

	//�ı䵱ǰ������Ŀ��
	void SetAimedTarget(AMonsterPaperFlipbookActor* const Target);

	//��ȡ��ǰ������Ŀ��
	AMonsterPaperFlipbookActor* GetAimedTarget()const;

	//ɱ������+1
	void AddKill();

	//�����ܹ�ɱ���Ĺ���
	int32 GetTotalKill()const;
	
protected:
	//��Ǯ��
	UPROPERTY(EditAnywhere)
	int32 Money;

	//��ǰ������Ŀ��
	AMonsterPaperFlipbookActor* CurrentAimedTarget;

	//�ܹ�ɱ���Ĺ���
	int32 TotalKill;
};
