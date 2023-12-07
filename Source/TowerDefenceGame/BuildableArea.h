// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BuildableArea.generated.h"

UCLASS()
class TOWERDEFENCEGAME_API ABuildableArea : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABuildableArea();

	UFUNCTION(BlueprintCallable, Category = "Mutex")
	void SetShutDownOthers();

	UFUNCTION(BlueprintCallable, Category = "Mutex")
	void RecoverShutDownOthers();

	UFUNCTION(BlueprintCallable, Category = "Mutex")
	bool GetShutDownOthers();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	static bool ShutDownOthers;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

//初始化静态成员
bool ABuildableArea::ShutDownOthers = false;