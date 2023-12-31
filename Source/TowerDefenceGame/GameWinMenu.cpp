// Fill out your copyright notice in the Description page of Project Settings.


#include "GameWinMenu.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UGameWinMenu::NativeConstruct()
{
	Super::NativeConstruct();
	if (UGameplayStatics::GetCurrentLevelName(GetWorld()) == FString("level2"))
	{
		RestartBtn->SetIsEnabled(false);
	}
	else
	{
		SaveCurrentGame();
	}
}

void UGameWinMenu::ClickRestartBtn()
{
	//UE_LOG(LogTemp, Warning, TEXT("continue game!"));
	UGameplayStatics::OpenLevel(GetWorld(), FName(FString("level2")));
}
