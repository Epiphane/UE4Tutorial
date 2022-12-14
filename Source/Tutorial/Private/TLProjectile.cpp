// Fill out your copyright notice in the Description page of Project Settings.


#include "TLProjectile.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ATLProjectile::ATLProjectile()
{
    SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
    SphereComp->SetCollisionProfileName("Projectile");
    RootComponent = SphereComp;

    EffectComp = CreateDefaultSubobject<UParticleSystemComponent>("EffectComp");
    EffectComp->SetupAttachment(SphereComp);

    MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComp");
    MovementComp->bRotationFollowsVelocity = true;
    MovementComp->bInitialVelocityInLocalSpace = true;
    MovementComp->ProjectileGravityScale = 0.0f;
    MovementComp->InitialSpeed = 8000.0f;
}

// Called when the game starts or when spawned
void ATLProjectile::BeginPlay()
{
	Super::BeginPlay();

    SphereComp->OnComponentHit.AddDynamic(this, &ATLProjectile::OnHit);
    SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ATLProjectile::OnActorOverlap);
    SphereComp->IgnoreActorWhenMoving(GetInstigator(), true);
}

void ATLProjectile::PostInitializeComponents()
{
    Super::PostInitializeComponents();

}

void ATLProjectile::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    CollideWith(OtherActor, OtherComp);
}

void ATLProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* Other, UPrimitiveComponent* OtherComponent, FVector Normal, const FHitResult& Hit)
{
    Explode();
}

void ATLProjectile::CollideWith_Implementation(AActor* Other, UPrimitiveComponent* OtherComponent)
{
    Explode();
}

void ATLProjectile::Explode_Implementation()
{
    if (ensure(!IsPendingKill()))
    {
        UGameplayStatics::SpawnEmitterAtLocation(this, ImpactVFX, GetActorLocation(), GetActorRotation());

        Destroy();
    }
}

