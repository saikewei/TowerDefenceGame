// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperFlipbookActor.h"
#include "MonsterPaperFlipbookActor.generated.h"

class USplineComponent;
class UUserwidget;
class UBoxComponent;
class ATShitBullet;
class UAudioComponent;
/**
 * 
 */

class UPaperFlipbookComponent;
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
	UFUNCTION(BlueprintImplementableEvent, Category = "Pin")
	void SetPinMarkVisibility(bool IsVisable);

	//����ͷ���Ǻſɼ���
	UFUNCTION(BlueprintImplementableEvent, Category = "HP")
	void SetHPBarPersentage(const float Persent);

	//����Ѫ���ɼ���
	UFUNCTION(BlueprintImplementableEvent, Category = "HP")
	void SetHPBarMarkVisibility(bool IsVisable);

	//������������
	void PlayDeadAnimation();

	//������Ƶ���
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UAudioComponent* SpawnAudioComponent;

	//������Ƶ���
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UAudioComponent* DeathAudioComponent;

	//��������
	UPROPERTY(EditAnywhere)
	UPaperFlipbookComponent* DeathAnimation;

	//��ʺ����
	UPROPERTY(EditAnywhere)
	UPaperFlipbookComponent* StepShitAnimation;

	//�������
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UPaperFlipbookComponent* MonsterAnimation;

	//��������
	virtual void Die();
};
