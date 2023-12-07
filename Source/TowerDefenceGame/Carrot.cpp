// Fill out your copyright notice in the Description page of Project Settings.


#include "Carrot.h"

// Sets default values
ACarrot::ACarrot()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	//����Ѫ��Ĭ��ֵ
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

//��ø��ܲ����˺�
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
	// ��Ѫ
	CarrotHealth -= DamageAmount;

	if (CarrotHealth <= 0.0f)
	{
		Destroy();
	}
}