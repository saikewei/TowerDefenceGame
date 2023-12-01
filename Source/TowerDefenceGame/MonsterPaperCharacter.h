// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "MonsterPaperCharacter.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENCEGAME_API AMonsterPaperCharacter : public APaperCharacter
{
	GENERATED_BODY()

public:
	AMonsterPaperCharacter();

	void MoveToWaypoint();

protected:
	void BeginPlay()override;

private:
	//��ǰ����·����Ĵ���
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	int32 CurrentWaypoint;

	TArray<AActor*> Waypoints;
};
