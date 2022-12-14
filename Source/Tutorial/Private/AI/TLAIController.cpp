// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/TLAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

void ATLAIController::BeginPlay()
{
    Super::BeginPlay();

    RunBehaviorTree(BehaviorTree);

    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
    if (PlayerPawn)
    {
        GetBlackboardComponent()->SetValueAsObject("TargetActor", PlayerPawn);
    }
}
