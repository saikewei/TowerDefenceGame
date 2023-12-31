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
	//����Ϸ��ʼʱ����
	virtual void BeginPlay() override;

	//ÿһ��tick����
	virtual void Tick(float DeltaTime) override;

	void ToggleCollision(bool Aimed);

protected:
	virtual void Die()override;
};
