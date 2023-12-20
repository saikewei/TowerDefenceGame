// Fill out your copyright notice in the Description page of Project Settings.


#include "TFan.h"

ATFan::ATFan()
{
	FireRate = 0.4f;
	AttackRange = 1200.f;
	DetectionSphere->SetSphereRadius(AttackRange);
	//设置相关金额
	UpgradeCost.Add(220);
	UpgradeCost.Add(260);
	SellCost.Add(128);
	SellCost.Add(304);
	SellCost.Add(512);
}
