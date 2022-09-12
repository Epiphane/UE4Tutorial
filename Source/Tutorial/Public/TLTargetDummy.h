// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TLTargetDummy.generated.h"

class UStaticMeshComponent;
class UTLAttributesComponent;

UCLASS()
class TUTORIAL_API ATLTargetDummy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATLTargetDummy();

protected:
    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* MeshComp;

	UPROPERTY(VisibleAnywhere)
	UTLAttributesComponent* AttributesComp;

protected:
	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor, UTLAttributesComponent* OwningComp, float NewHealth, float Delta);
};
