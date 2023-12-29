// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"
#include "TowerBase.generated.h"

// ǰ������
class UBuildMenu;
class WB_BuildMenuWidget;
class ATowerPaperFlipbookActor;

UCLASS()
class TOWERDEFENCEGAME_API ATowerBase : public AActor
{
	GENERATED_BODY()
	friend class UBuildMenu;
public:	
	// Sets default values for this actor's properties
	ATowerBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//����ָ����˵���ָ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TowerBase")
	UBuildMenu* Menu;

	//��λ���Ƿ���ڷ�����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TowerBase")
	bool IsTower;

	//�������¼�
	virtual void NotifyActorOnClicked(FKey ButtonPressed = EKeys::LeftMouseButton) override;

	//ɾ����������������ʾ
	void SetOtherBasesInvisible();

	//������ײ���
	UPROPERTY(EditAnywhere, Category = "Components")
	UBoxComponent* CollisionBox;

	//��ͼUI��
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UBuildMenu> BuildMenuBlueprintClass;

	//��λ���Ƿ���ڼӺ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TowerBase")
	bool IsPlusSign;

	//�ƶ��˵Ĵ����¼�
	virtual void NotifyActorOnInputTouchBegin(const ETouchIndex::Type FingerIndex)override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//���������Ӻſɼ���
	UFUNCTION(BlueprintImplementableEvent, Category = "Tower")
	void ToggleSignVsibility(bool IsBaseVisible);

	//�������������ɼ���
	void SetBaseVisibility(bool Visible);

	//���ø������Ƿ��з�����
	void SetIsTower(bool NewIsTower);

};
