// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperFlipbook.h"
#include "PaperFlipbookActor.h"
#include "PaperFlipbookComponent.h"
#include "Carrot.generated.h"

UCLASS()
class TOWERDEFENCEGAME_API ACarrot : public APaperFlipbookActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACarrot();

	UFUNCTION()
	void MyTakeDamage(float DamageAmount);
	void UpdateFlipbook(); //根据萝卜血量更新Flipbook


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Flipbook", meta = (AllowPrivateAccess = "true"))
		UPaperFlipbook* Carrot_1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Flipbook", meta = (AllowPrivateAccess = "true"))
		UPaperFlipbook* Carrot_2;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Flipbook", meta = (AllowPrivateAccess = "true"))
		UPaperFlipbook* Carrot_3;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Flipbook", meta = (AllowPrivateAccess = "true"))
		UPaperFlipbook* Carrot_4;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Flipbook", meta = (AllowPrivateAccess = "true"))
		UPaperFlipbook* Carrot_5;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Carrot")
	float CarrotHealth; // 萝卜血量

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Flipbook")
	class UPaperFlipbookComponent* FlipbookComponent;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	//获得给萝卜的伤害
	UFUNCTION(BlueprintCallable, Category = "Damage")
	void GetDamage(float Damage);
};
