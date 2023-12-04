// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperFlipbookActor.h"
#include "MonsterPaperFlipbookActor.generated.h"

class USplineComponent;

/**
 * 
 */
UCLASS()
class TOWERDEFENCEGAME_API AMonsterPaperFlipbookActor : public APaperFlipbookActor
{
	GENERATED_BODY()
public:
	AMonsterPaperFlipbookActor();
	
	//传入本关卡样条线路径
	void SetPath(const USplineComponent* Path);

	//传入本关卡销毁位置
	void SetEndLocation(const FVector& End);

	//在游戏开始时调用
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Damage") 
	void GetDamage(float Damage);

protected:
	//本角色所跟随的路径
	const USplineComponent* MyPath;

	//移动速度
	UPROPERTY(EditAnywhere)
	float MovingSpeed;

	//当前在路径中的位置
	float CurrentLocation;

	//销毁位置
	FVector EndLoaction;

	//怪物血量
	UPROPERTY(EditAnywhere)
	float HP;

	//血条组件
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Info, meta = (AllowPrivateAccess = "true"))
	//class UWidgetComponent* InfoWidgetComponent;
};
