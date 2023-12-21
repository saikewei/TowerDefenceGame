// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Bullet.h"
#include "TFanBullet.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENCEGAME_API ATFanBullet : public ABullet
{
	GENERATED_BODY()
public:
	ATFanBullet();
	virtual void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
