// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Waypoint.generated.h"

UCLASS()
class TOWERDEFENCEGAME_API AWaypoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWaypoint();
	//���ص�ǰ·�������
	int GetWaypiontOrder();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	//·����Ĵ���
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	int32 WaypointOrder;
};