// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Bullet.h"
#include "PaperFlipbookActor.h"
#include "MonsterPaperFlipbookActor.h"
#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"
#include "PaperFlipbookComponent.h"
#include "UpgradeSellMenu.h"
#include "ToweDefenceGameState.h"
#include "TowerPaperFlipbookActor.generated.h"

/**
 *
 */
class UButton;
class ATowerBase;
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

	// �������¼�
	virtual void NotifyActorOnClicked(FKey ButtonPressed = EKeys::LeftMouseButton) override;

	// ��������UI�ɼ�
	void SetSelfVisibility(bool Visible);

	// ��������UI���ɼ�
	void SetOthersInvisible();

	// ��ǰ�������ļ���
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Tower")
	int32 CurrentLevel = 0;

	// ��������������
	UPROPERTY(EditAnywhere, Category = "LevelCost")
	TArray<int32>UpgradeCost;

	// ���������۷���
	UPROPERTY(EditAnywhere, Category = "LevelCost")
	TArray<int32>SellCost;

protected:
	//�����������뾶
	UPROPERTY(EditAnywhere, Category = "Basic")
	float AttackRange = 1000.f;

	//������ײ��
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* DetectionSphere;

	////���������ײ��
	//UPROPERTY(EditAnywhere, Category = "Components")
	//UBoxComponent* CollisionBox;

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
	UPROPERTY(EditAnywhere, Category = "Shooting")
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

	UPROPERTY(EditAnywhere,Category="Tower")
	bool IsVisible;

	// ��ͼUI��
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUpgradeSellMenu> UpgradeSellMenuBlueprintClass;

	// ����ָ��˵���ָ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tower")
	UUpgradeSellMenu* Menu;

};
