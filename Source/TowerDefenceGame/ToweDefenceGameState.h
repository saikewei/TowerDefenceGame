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

	//获得当前金钱
	UFUNCTION(BlueprintCallable)
	int32 GetMoney()const;

	//添加金钱（负值为减少）,金钱添加成功则返回真
	UFUNCTION(BlueprintCallable)
	bool AddMoney(int32 MoneyToAdd);

	//改变当前锁定的目标
	void SetAimedTarget(AMonsterPaperFlipbookActor* const Target);

	//获取当前锁定的目标
	AMonsterPaperFlipbookActor* GetAimedTarget()const;
	
protected:
	//金钱数
	UPROPERTY(EditAnywhere)
	int32 Money;

	//当前锁定的目标
	AMonsterPaperFlipbookActor* CurrentAimedTarget;
};
