// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperFlipbook.h"
#include "PaperFlipbookActor.h"
#include "PaperFlipbookComponent.h"
#include "ToweDefenceGameState.h"
#include "UpgradeCarrotMenu.h"
#include "Kismet/GameplayStatics.h"
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
	void UpdateFlipbook(); //�����ܲ�Ѫ������Flipbook
	void UpgradeCarrot();
	virtual void NotifyActorOnClicked(FKey ButtonPressed = EKeys::LeftMouseButton) override;
	void SetSelfVisibility(bool Visible);
	virtual void NotifyActorOnInputTouchBegin(const ETouchIndex::Type FingerIndex) override;

	//��ͼUI��
	UPROPERTY(EditDefaultsOnly, Category = "UI")
		TSubclassOf<UUpgradeCarrotMenu> UpgradeSellMenuBlueprintClass;

	//����ָ��˵���ָ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Carrot")
		UUpgradeCarrotMenu* Menu;


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
	float CarrotHealth; // �ܲ�Ѫ��

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Flipbook")
	class UPaperFlipbookComponent* FlipbookComponent;

	UPROPERTY(EditAnywhere, Category = "Carrot")
		bool IsVisible;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	//��ø��ܲ����˺�
	UFUNCTION(BlueprintCallable, Category = "Damage")
	void GetDamage(float Damage);
};
