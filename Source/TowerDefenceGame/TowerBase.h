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

UCLASS()
class TOWERDEFENCEGAME_API ATowerBase : public AActor
{
	GENERATED_BODY()
public:	
	// Sets default values for this actor's properties
	ATowerBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// ����ָ����˵���ָ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TowerBase")
	UBuildMenu* Menu;

	// ��λ���Ƿ���ڷ�����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TowerBase")
	bool IsTower;

	// ��λ���Ƿ���ڼӺ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TowerBase")
	bool IsPlusSign;

	// �������¼�
	virtual void NotifyActorOnClicked(FKey ButtonPressed = EKeys::LeftMouseButton) override;

	// ɾ����������������ʾ
	void SetOtherBasesInvisible();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// ���������Ӻſɼ���
	UFUNCTION(BlueprintImplementableEvent, Category = "Tower")
	void ToggleSignVsibility(bool IsBaseVisible);

	// �������������ɼ���
	void SetBaseVisibility(bool Visible);

	// ������ײ���
	UPROPERTY(EditAnywhere, Category = "Components")
	UBoxComponent* CollisionBox;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UBuildMenu> BuildMenuBlueprintClass;


};
