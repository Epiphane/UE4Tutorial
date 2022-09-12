// Fill out your copyright notice in the Description page of Project Settings.


#include "TLMagicProjectile.h"
#include "TLAttributesComponent.h"
#include "Components/AudioComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

void ATLMagicProjectile::Explode_Implementation()
{
    Super::Explode_Implementation();

    if (ensure(ImpactSound))
    {
        UGameplayStatics::PlaySoundAtLocation(GetWorld(), ImpactSound, GetActorLocation());
    }
}

ATLMagicProjectile::ATLMagicProjectile()
{
    AudioComp = CreateDefaultSubobject<UAudioComponent>("AudioComp");
    AudioComp->SetupAttachment(RootComponent);
}

void ATLMagicProjectile::CollideWith_Implementation(AActor* Other, UPrimitiveComponent* OtherComponent)
{
    if (Other && Other != GetInstigator())
    {
        Explode();

        UTLAttributesComponent* Attributes = Cast<UTLAttributesComponent>(Other->GetComponentByClass(UTLAttributesComponent::StaticClass()));
        if (Attributes)
        {
            UE_LOG(LogTemp, Log, TEXT("Collided with %s"), *Other->GetName());
            Attributes->ApplyHealthChange(-Damage);

            UGameplayStatics::PlayWorldCameraShake(GetWorld(), Shake, GetActorLocation(), 0.0f, 200.0f);
        }
    }
}
