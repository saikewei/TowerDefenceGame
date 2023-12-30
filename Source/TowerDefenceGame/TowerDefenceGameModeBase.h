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
	ATowerDefenceGameModeBase();

	//����ͣ�˵�
	void OpenPauseMenu();

	//��Ϸʧ��
	void GameLost();

	//��Ϸ�ɹ�
	void GameWin();

	//��ȡ��ǰ���ﲨ��
	UFUNCTION(BlueprintCallable)
	int32 GetCurrentWave()const;

	//��ȡ��ǰ�ؿ����
	UFUNCTION(BlueprintCallable)
	int32 GetCurrentLevelNum()const;

protected:
	//����Ϸ��ʼʱ����
	virtual void BeginPlay() override;

	//ÿһ��tick����
	virtual void Tick(float DeltaTime) override;

	//ˢ��һ������
	void SpawnMonster();

	//��ǰ����
	int32 currentWave;

	//����ˢ�¶�ʱ��
	FTimerHandle SpawnHandle;

	//�ж���Ϸ������ʱ��
	FTimerHandle WaitForEnd;

	//ÿһ��������
	UPROPERTY(EditAnywhere)
	TArray<int32> monsterPerWave;

	//��ǰ������
	int32 totalMonster;

	//��ǰ�ؿ�
	UPROPERTY(EditAnywhere)
	int32 levelNum;

	//ˢ�µĹ���
	UPROPERTY(EditAnywhere)
	TSubclassOf<AMonsterPaperFlipbookActor> MonsterToSpawn;

	//ˢ�µĶ��ֹ���
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<AMonsterPaperFlipbookActor>> MonstersList;

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

	//��Ϸ�ɹ��˵����
	UPROPERTY(EditAnywhere, Category = "GameWinMenu")
	TSubclassOf<UUserWidget> GameWinMenu_Class;
	UUserWidget* GameWinMenuWidget;



	//������һ������
	void StartNextWave();
};
