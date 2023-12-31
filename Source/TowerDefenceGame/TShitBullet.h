// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Bullet.h"
#include "TShitBullet.generated.h"

/**
 * 
 */
class AMonsterPaperFlipbookActor;
UCLASS()
class TOWERDEFENCEGAME_API ATShitBullet : public ABullet
{
	GENERATED_BODY()
	
public:
	ATShitBullet();
	virtual void OnHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	UFUNCTION(BlueprintCallable)
	void Decelerate(AMonsterPaperFlipbookActor* Monster);

protected:
	UPROPERTY(BlueprintReadWrite, CateGory="Deceleration")
	float DecerlerationTime;
	
};
