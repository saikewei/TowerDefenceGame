// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuGameModeBase.h"
#include "TowerDefenceSaveGame.h"
#include "Kismet/GameplayStatics.h"

void AMainMenuGameModeBase::BeginPlay()
{
	UTowerDefenceSaveGame* SaveGameInstance;

	SaveGameInstance = Cast<UTowerDefenceSaveGame>(UGameplayStatics::LoadGameFromSlot("slot7", 1));

	if(SaveGameInstance)
	{
		IsLevel2Availible = SaveGameInstance->IsLevel2Availible();
		UE_LOG(LogTemp, Warning, TEXT("load success! Result:%d"), SaveGameInstance->num);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("load fail!"));
		IsLevel2Availible = false;
	}
}