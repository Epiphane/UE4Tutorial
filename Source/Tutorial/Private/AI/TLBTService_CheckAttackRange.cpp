// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/TLBTService_CheckAttackRange.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIModule/Classes/AIController.h"

void UTLBTService_CheckAttackRange::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    // Check distance between AI pawn and target actor

    UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
    if (ensure(Blackboard))
    {
        AActor* TargetActor = Cast<AActor>(Blackboard->GetValueAsObject("TargetActor"));

        if (TargetActor)
        {
            AAIController* MyController = OwnerComp.GetAIOwner();
            if (ensure(MyController))
            {
                APawn* AIPawn = MyController->GetPawn();
                if (ensure(AIPawn))
                {
                    float Distance = FVector::Distance(TargetActor->GetActorLocation(), AIPawn->GetActorLocation());
                    bool bWithinRange = Distance < 2000.f;

                    bool bHasLineOfSight = false;
                    if (bWithinRange)
                    {
                        bHasLineOfSight = MyController->LineOfSightTo(TargetActor);
                    }

                    Blackboard->SetValueAsBool(AttackRangeKey.SelectedKeyName, bWithinRange && bHasLineOfSight);
                }
            }
        }
    }
}
