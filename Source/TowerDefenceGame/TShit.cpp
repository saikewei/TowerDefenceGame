// Fill out your copyright notice in the Description page of Project Settings.


#include "TShit.h"

ATShit::ATShit()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	FireRate = 0.4f;
	AttackRange = 800.f;
	DetectionSphere->SetSphereRadius(AttackRange);
	//设置相关金额
	UpgradeCost.Add(220);
	UpgradeCost.Add(260);
	SellCost.Add(96);
	SellCost.Add(272);
	SellCost.Add(480);
}

void ATShit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ChooseTargetMonster();
}
