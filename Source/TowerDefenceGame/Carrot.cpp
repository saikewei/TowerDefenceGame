// Fill out your copyright notice in the Description page of Project Settings.


#include "Carrot.h"

// Sets default values
ACarrot::ACarrot()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	//设置血量默认值
	CarrotHealth = 100.0f;

}

// Called when the game starts or when spawned
void ACarrot::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ACarrot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//获得给萝卜的伤害
void ACarrot::GetDamage(float Damage)
{
	CarrotHealth -= Damage;
	if (CarrotHealth < 0)
	{
		CarrotHealth = 0;
	}
}

void ACarrot::TakeDamage(float DamageAmount)
{
	// 减血
	CarrotHealth -= DamageAmount;

	if (CarrotHealth <= 0.0f)
	{
		Destroy();
	}
}