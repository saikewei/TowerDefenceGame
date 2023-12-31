// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"
#include "TowerBase.generated.h"

// 前向声明
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

	//创建指向建造菜单的指针
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TowerBase")
	UBuildMenu* Menu;

	//该位置是否存在防御塔
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TowerBase")
	bool IsTower;

	//处理点击事件
	virtual void NotifyActorOnClicked(FKey ButtonPressed = EKeys::LeftMouseButton) override;

	//删除所有其他塔基显示
	void SetOtherBasesInvisible();

	//盒体碰撞组件
	UPROPERTY(EditAnywhere, Category = "Components")
	UBoxComponent* CollisionBox;

	//蓝图UI类
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UBuildMenu> BuildMenuBlueprintClass;

	//该位置是否存在加号
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TowerBase")
	bool IsPlusSign;

	//移动端的触摸事件
	virtual void NotifyActorOnInputTouchBegin(const ETouchIndex::Type FingerIndex)override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//设置塔基加号可见性
	UFUNCTION(BlueprintImplementableEvent, Category = "Tower")
	void ToggleSignVsibility(bool IsBaseVisible);

	//设置整体塔基可见性
	void SetBaseVisibility(bool Visible);

	//设置该塔基是否有防御塔
	void SetIsTower(bool NewIsTower);

};
