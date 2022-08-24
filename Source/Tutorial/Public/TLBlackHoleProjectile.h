// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TLProjectile.h"
#include "TLBlackHoleProjectile.generated.h"

class URadialForceComponent;
class USphereComponent;

UCLASS()
class TUTORIAL_API ATLBlackHoleProjectile : public ATLProjectile
{
	GENERATED_BODY()

protected:
    UPROPERTY(EditAnywhere)
    float Lifetime = 5.0f;

protected:
    UPROPERTY(VisibleAnywhere)
    URadialForceComponent* RadialForce;

    FTimerHandle TimerHandle_ParticleLifetime;

protected:
    ATLBlackHoleProjectile();

    void BeginPlay() override;

protected:
    void OnHit(UPrimitiveComponent* HitComponent, AActor* Other, UPrimitiveComponent* OtherComponent, FVector Normal, const FHitResult& Hit) override;
};
