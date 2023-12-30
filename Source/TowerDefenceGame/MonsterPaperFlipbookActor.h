// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperFlipbookActor.h"
#include "MonsterPaperFlipbookActor.generated.h"

class USplineComponent;
class UUserwidget;
class UBoxComponent;
class ATShitBullet;
/**
 * 
 */
UCLASS()
class TOWERDEFENCEGAME_API AMonsterPaperFlipbookActor : public APaperFlipbookActor
{
	GENERATED_BODY()

	friend class ATShitBullet;
public:
	AMonsterPaperFlipbookActor();
	
	//���뱾�ؿ�������·��
	void SetPath(const USplineComponent* Path);

	//����Ϸ��ʼʱ����
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Damage") 
	void GetDamage(float Damage);

	UFUNCTION(BlueprintCallable, Category = "Bonus")
	int32 GetBonus()const;

	//�ı䵱ǰ������״̬
	void ChangeIsAimed();

	//��õ�ǰ������״̬
	bool GetIsAimed() const;

protected:
	//����ɫ�������·��
	const USplineComponent* MyPath;

	//��ײ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UBoxComponent* CollisionBox;

	//�ƶ��ٶ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MovingSpeed;

	//��ʼ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float OriginalSpeed;

	//��ǰ��·���е�λ��
	float CurrentLocation;

	//�Ƿ�����
	bool IsAimed;

	//����Ѫ��
	UPROPERTY(BlueprintReadOnly, Category = "Health")
	float HP;

	//����Ѫ������
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Health")
	float MAX_HP;

	//���ܲ���ɵ��˺�
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Damage")
	float DamageForCarrot;

	//��ɱ�õ��Ľ�ҽ���
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Bonus")
	int32 KillBonus;

	//���õ���¼�
	virtual void NotifyActorOnClicked(FKey ButtonPressed = EKeys::LeftMouseButton) override;

	//�ƶ��˵Ĵ����¼�
	virtual void NotifyActorOnInputTouchBegin(const ETouchIndex::Type FingerIndex)override;

	//����ͷ���Ǻſɼ���
	UFUNCTION(BlueprintImplementableEvent, Category = "Tower")
	void SetPinMarkVisibility(bool IsVisable);

	UFUNCTION(BlueprintImplementableEvent, Category = "Death")
	void PlayDeadAnimation();

	void Die();
};
