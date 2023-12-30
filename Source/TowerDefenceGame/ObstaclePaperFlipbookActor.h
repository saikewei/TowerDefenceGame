// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MonsterPaperFlipbookActor.h"
#include "ObstaclePaperFlipbookActor.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENCEGAME_API AObstaclePaperFlipbookActor : public AMonsterPaperFlipbookActor
{
	GENERATED_BODY()
	AObstaclePaperFlipbookActor();
public:
	//在游戏开始时调用
	virtual void BeginPlay() override;

	void ToggleCollision(bool Aimed);
};
