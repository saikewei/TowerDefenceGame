// Fill out your copyright notice in the Description page of Project Settings.


#include "ToweDefenceGameState.h"

int32 AToweDefenceGameState::GetMoney() const
{
	return Money;
}

bool AToweDefenceGameState::AddMoney(int32 MoneyToAdd)
{
	if (MoneyToAdd + Money >= 0)
	{
		Money += MoneyToAdd;
		return true;
	}
	return false;
}
