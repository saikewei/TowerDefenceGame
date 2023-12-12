// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TowerDefenceGameModeBase.generated.h"

class AMonsterPaperFlipbookActor;
class ASplinePathActor;

/**
 * 
 */
UCLASS()
class TOWERDEFENCEGAME_API ATowerDefenceGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	//����ͣ�˵�
	void OpenPauseMenu();

	//��Ϸʧ��
	void GameLost();

protected:
	//����Ϸ��ʼʱ����
	virtual void BeginPlay() override;

	//ÿһ��tick����
	virtual void Tick(float DeltaTime) override;

	//ˢ��һ������
	void SpawnMonster();

	//ˢ�µĹ���
	UPROPERTY(EditAnywhere)
	TSubclassOf<AMonsterPaperFlipbookActor> MonsterToSpawn;

	//����ˢ��λ��
	UPROPERTY(EditAnywhere)
	FVector SpawnLocation;

	//���ؿ���·��
	UPROPERTY(EditAnywhere)
	UClass* Path;

	//HUD���
	UPROPERTY(EditAnywhere, Category = "UI HUD")
	TSubclassOf<UUserWidget> HUD_Class;
	UUserWidget* HUDWidget;

	//��ͣ�˵����
	UPROPERTY(EditAnywhere, Category = "PauseMenu")
	TSubclassOf<UUserWidget> PauseMenu_Class;
	UUserWidget* PauseMenuWidget;

	//��Ϸʧ�ܲ˵����
	UPROPERTY(EditAnywhere, Category = "GameLostMenu")
	TSubclassOf<UUserWidget> GameLostMenu_Class;
	UUserWidget* GameLostMenuWidget;
};
