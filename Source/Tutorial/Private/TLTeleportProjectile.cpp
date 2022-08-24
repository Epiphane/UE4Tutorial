// Fill out your copyright notice in the Description page of Project Settings.


#include "TLTeleportProjectile.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

ATLTeleportProjectile::ATLTeleportProjectile()
    : ATLProjectile()
{
    MovementComp->InitialSpeed = 2500.0f;
}

void ATLTeleportProjectile::BeginPlay()
{
    Super::BeginPlay();

    GetWorldTimerManager().SetTimer(TimerHandle_DelayedDetonate, this, &ATLTeleportProjectile::Explode, DetonateDelay);
}

void ATLTeleportProjectile::Explode_Implementation()
{
    GetWorldTimerManager().ClearTimer(TimerHandle_DelayedDetonate);

    UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactVFX, GetActorLocation(), GetActorRotation());
    EffectComp->DeactivateSystem();
    MovementComp->StopMovementImmediately();
    SetActorEnableCollision(false);

    FTimerHandle TimerHandle_DelayedTeleport;
    GetWorldTimerManager().SetTimer(TimerHandle_DelayedTeleport, this, &ATLTeleportProjectile::TeleportPlayer, 0.2f);
}

void ATLTeleportProjectile::TeleportPlayer()
{
    AActor* MyInstigator = GetInstigator();
    if (ensure(MyInstigator))
    {
        GetInstigator()->TeleportTo(GetActorLocation(), GetInstigator()->GetActorRotation(), false, false);
        Destroy();
    }
}
