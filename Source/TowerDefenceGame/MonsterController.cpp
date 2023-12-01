// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterController.h"
#include "MonsterPaperCharacter.h"

void AMonsterController::BeginPlay()
{

}

void AMonsterController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	//获取控制器正在控制的角色
	AMonsterPaperCharacter* MyMonster = Cast<AMonsterPaperCharacter>(GetPawn());

	if (MyMonster)
	{
		//移到下一个路径点
		MyMonster->MoveToWaypoint();
	}
}
