// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerDefenceSaveGame.h"

UTowerDefenceSaveGame::UTowerDefenceSaveGame()
{
	//Level2Availible = true;
	num = 6;
}

void UTowerDefenceSaveGame::EnableLevel2()
{
	UE_LOG(LogTemp, Warning, TEXT("Set enable!"));
	Level2Availible = true;
}

bool UTowerDefenceSaveGame::IsLevel2Availible() const
{
	return Level2Availible;
}
