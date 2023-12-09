// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Bullet.h"
#include "PaperFlipbookActor.h"
#include "MonsterPaperFlipbookActor.h"
#include "Components/SphereComponent.h"
#include "PaperFlipbookComponent.h"
#include "TowerPaperFlipbookActor.generated.h"

/**
 *
 */
UCLASS()
class TOWERDEFENCEGAME_API ATowerPaperFlipbookActor : public APaperFlipbookActor
{
	GENERATED_BODY()

public:
	ATowerPaperFlipbookActor();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void BeginPlay() override;

	//���������
	void OnMonsterEnterDetectionRange(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	//�������뿪
	void OnMonsterLeaveDetectionRange(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	// ѡ��Ŀ�����
	AMonsterPaperFlipbookActor* ChooseTargetMonster();

	//��Ŀ�깥��
	void FireAtTarget();

	//����������
	void UpgradeTower();

	//�۳�������
	void SellTower();

protected:
	//�����������뾶
	UPROPERTY(EditAnywhere, Category = "Basic")
	float AttackRange = 1000.f;

	//������ײ��
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* DetectionSphere;

	// �����б�
	UPROPERTY(BlueprintReadWrite, Category = "Detection")
	TArray<AMonsterPaperFlipbookActor*> MonstersInRange;

	// Ŀ�����
	UPROPERTY(BlueprintReadWrite, Category = "Detection")
	AMonsterPaperFlipbookActor* TargetMonster = nullptr;

	// �ӵ��������
	UPROPERTY(EditDefaultsOnly, Category = "Shooting")
	TSubclassOf<ABullet> BulletClass;

	// �ӵ������ʱ����
	UPROPERTY(EditDefaultsOnly, Category = "Shooting")
	float FireRate;

	// ��ʱ�����
	FTimerHandle TimerHandle_FireRate;

	// ��������ת����
	UPROPERTY(EditAnywhere, Category = "Rotation")
	FRotator TowerRotation;

	// ��������
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UPaperFlipbookComponent* TowerFlipbook;

	// ��ͬ�ȼ��������������
	UPROPERTY(EditDefaultsOnly, Category = "Tower")
	TArray<UPaperFlipbook*> TowerLevelsFlipbooks;

	// ��ǰ�������ļ���
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tower")
	int32 CurrentLevel = 0;

	UPROPERTY(EditAnywhere,Category="LevelCost")
	int32 LevelOneCost = 0;

	UPROPERTY(EditAnywhere, Category = "LevelCost")
	int32 LevelTwoCost = 0;

	UPROPERTY(EditAnywhere, Category = "SellAmount")
	int32 LevelZeroSold = 0;

	UPROPERTY(EditAnywhere, Category = "SellAmount")
	int32 LevelOneSold = 0;

	UPROPERTY(EditAnywhere, Category = "SellAmount")
	int32 LevelTwoSold = 0;

};
