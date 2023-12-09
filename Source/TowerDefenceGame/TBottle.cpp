// Fill out your copyright notice in the Description page of Project Settings.


#include "TBottle.h"

ATBottle::ATBottle()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//设置相关金额
	BuildCost = 100;
	LevelOneCost = 180;
	LevelZeroSold = 80;
	LevelTwoCost = 260;
	LevelOneSold = 224;
	LevelTwoSold = 432;
}

void ATBottle::RotateToTarget()
{
	if (TargetMonster)
	{
		// 计算新的朝向
		FVector Direction = (TargetMonster->GetActorLocation() - GetActorLocation()).GetSafeNormal();
		FRotator NewRotation = FRotationMatrix::MakeFromZ(Direction).Rotator();
		SetActorRotation(NewRotation);
	}
}

void ATBottle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ChooseTargetMonster();
	RotateToTarget();
}
