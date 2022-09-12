// Fill out your copyright notice in the Description page of Project Settings.


#include "TLBlackHoleProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"

ATLBlackHoleProjectile::ATLBlackHoleProjectile()
    : ATLProjectile()
{
    RadialForce = CreateDefaultSubobject<URadialForceComponent>("RadialForce");
    RadialForce->SetupAttachment(SphereComp);
    RadialForce->ForceStrength = -1000;
    RadialForce->Radius = 500;
    RadialForce->SetAutoActivate(true);
    RadialForce->AddCollisionChannelToAffect(ECC_WorldDynamic);
    RadialForce->AddCollisionChannelToAffect(ECC_WorldStatic);
    RadialForce->AddCollisionChannelToAffect(ECC_PhysicsBody);
    RadialForce->bIgnoreOwningActor = true;

    MovementComp->InitialSpeed = 200;
}

void ATLBlackHoleProjectile::BeginPlay()
{
    Super::BeginPlay();

    GetWorldTimerManager().SetTimer(TimerHandle_ParticleLifetime, this, &ATLBlackHoleProjectile::Explode, Lifetime);
}

void ATLBlackHoleProjectile::CollideWith_Implementation(AActor* Other, UPrimitiveComponent* OtherComponent)
{
    if (!Other->IsPendingKill() && OtherComponent->IsSimulatingPhysics())
    {
        Other->Destroy();
    }
}

void ATLBlackHoleProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* Other, UPrimitiveComponent* OtherComponent, FVector Normal, const FHitResult& Hit)
{
    if (!Other->IsPendingKill() && OtherComponent->IsSimulatingPhysics())
    {
        Other->Destroy();
    }
}

