// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TLAIController.generated.h"

/**
 * 
 */
UCLASS()
class TUTORIAL_API ATLAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	UBehaviorTree* BehaviorTree;

protected:
	virtual void BeginPlay() override;
};
