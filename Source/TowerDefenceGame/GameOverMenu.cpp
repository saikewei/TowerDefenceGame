// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOverMenu.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UGameOverMenu::NativeConstruct()
{
	Super::NativeConstruct();
	//�󶨵���¼�
	RestartBtn->OnClicked.AddDynamic(this, &UGameOverMenu::ClickRestartBtn);
	ExitBtn->OnClicked.AddDynamic(this, &UGameOverMenu::ClickExitBtn);

	//��������ģʽʹ�����ֻ�ܲٿز˵�
	GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeUIOnly().SetWidgetToFocus(TakeWidget()));
}

void UGameOverMenu::ClickRestartBtn()
{
	//���´򿪵�ǰ�ؿ�
	UGameplayStatics::OpenLevel(GetWorld(), FName(UGameplayStatics::GetCurrentLevelName(GetWorld())));
}

void UGameOverMenu::ClickExitBtn()
{
	//�ص����˵�
	UGameplayStatics::OpenLevel(GetWorld(), NameOfMainLevel);
}
