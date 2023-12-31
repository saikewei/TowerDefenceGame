// Fill out your copyright notice in the Description page of Project Settings.


#include "HPBarWidget.h"
#include "Components/ProgressBar.h"

void UHPBarWidget::SetPersent(const float NewPersent)
{
	
	if (NewPersent >= 0)
	{
		Persentage = NewPersent;
	}
	else
	{
		Persentage = 0.f;
	}
	//UE_LOG(LogTemp, Warning, TEXT("persent:%f"), Persentage);
}
