// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperFlipbookActor.h"
#include "Carrot.generated.h"

UCLASS()
class TOWERDEFENCEGAME_API ACarrot : public APaperFlipbookActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACarrot();

	UFUNCTION()
	void TakeDamage(float DamageAmount);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Carrot")
	float CarrotHealth; // 萝卜血量

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	//获得给萝卜的伤害
	UFUNCTION(BlueprintCallable, category = "Damage")
	void GetDamage(float Damage);
};
