// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperFlipbookActor.h"
#include "MonsterPaperFlipbookActor.generated.h"

class USplineComponent;

/**
 * 
 */
UCLASS()
class TOWERDEFENCEGAME_API AMonsterPaperFlipbookActor : public APaperFlipbookActor
{
	GENERATED_BODY()
public:
	AMonsterPaperFlipbookActor();
	
	//���뱾�ؿ�������·��
	void SetPath(const USplineComponent* Path);

	//���뱾�ؿ�����λ��
	void SetEndLocation(const FVector& End);

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	//����ɫ�������·��
	const USplineComponent* MyPath;

	//�ƶ��ٶ�
	UPROPERTY(EditAnywhere)
	float MovingSpeed;

	//��ǰ��·���е�λ��
	float CurrentLocation;

	//����λ��
	FVector EndLoaction;
};
