// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterPaperCharacter.h"
#include "MonsterController.h"
#include "Waypoint.h"
#include "Kismet/GameplayStatics.h"

AMonsterPaperCharacter::AMonsterPaperCharacter()
{

}

void AMonsterPaperCharacter::MoveToWaypoint()
{
	//获得正在控制这个角色的控制器
	AMonsterController* MyController = Cast<AMonsterController>(GetController());
	
	if (MyController)
	{
		
		if (CurrentWaypoint <= Waypoints.Num())
		{
			for (AActor* Waypoint : Waypoints)
			{
				AWaypoint* WaypointIter = Cast<AWaypoint>(Waypoint);

				if (WaypointIter)
				{
					if (WaypointIter->GetWaypiontOrder() == CurrentWaypoint)
					{
						MyController->MoveToActor(WaypointIter, 0.f, false);
						++CurrentWaypoint;
						UE_LOG(LogTemp, Warning, TEXT("Move"));
						break;
					}
				}
			}
		}
	}
}

void AMonsterPaperCharacter::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Start"));
	//获得所有路径点
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AWaypoint::StaticClass(), Waypoints);
	MoveToWaypoint();
}

