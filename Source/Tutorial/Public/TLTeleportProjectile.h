// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TLProjectile.h"
#include "TLTeleportProjectile.generated.h"

/**
 * 
 */
UCLASS()
class TUTORIAL_API ATLTeleportProjectile : public ATLProjectile
{
	GENERATED_BODY()

protected:
    UPROPERTY(EditDefaultsOnly, Category = "Teleport")
    float TeleportDelay = 0.2f;

    UPROPERTY(EditDefaultsOnly, Category = "Teleport")
    float DetonateDelay = 0.2f;

protected:
    FTimerHandle TimerHandle_DelayedDetonate;

protected:
    ATLTeleportProjectile();

    void BeginPlay() override;

protected:
    void Explode_Implementation() override;

    UFUNCTION()
    void TeleportPlayer();
};
