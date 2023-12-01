// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterController.h"
#include "MonsterPaperCharacter.h"

void AMonsterController::BeginPlay()
{

}

void AMonsterController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	//��ȡ���������ڿ��ƵĽ�ɫ
	AMonsterPaperCharacter* MyMonster = Cast<AMonsterPaperCharacter>(GetPawn());

	if (MyMonster)
	{
		//�Ƶ���һ��·����
		MyMonster->MoveToWaypoint();
	}
}
