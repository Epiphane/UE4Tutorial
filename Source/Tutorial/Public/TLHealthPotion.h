// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TLGameplayInterface.h"
#include "TLHealthPotion.generated.h"

class UCapsuleComponent;

UCLASS()
class TUTORIAL_API ATLHealthPotion : public AActor, public ITLGameplayInterface
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	float HealAmount = 50;

protected:
    UPROPERTY(VisibleAnywhere)
	UCapsuleComponent* CapsuleComp;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* StaticMesh;

	FTimerHandle TimerHandle_Reactivate;
	
public:	
	// Sets default values for this actor's properties
    ATLHealthPotion();

    void Interact_Implementation(APawn* InstigatorPawn) override;

protected:
	void Reactivate();
};
