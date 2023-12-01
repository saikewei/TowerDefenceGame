// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MonsterController.generated.h"

/**
 * 
 */


UCLASS()
class TOWERDEFENCEGAME_API AMonsterController : public AAIController
{
	GENERATED_BODY()
	
protected:

	//����Ϸ��ʼʱ����
	virtual void BeginPlay() override;

	//ÿ���ƶ���һ��·�������ô˺���
	virtual void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;
};
