// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TLProjectile.generated.h"

class USphereComponent;
class UParticleSystem;
class UParticleSystemComponent;
class UProjectileMovementComponent;

UCLASS()
class TUTORIAL_API ATLProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATLProjectile();

protected:
    UPROPERTY(EditDefaultsOnly, Category = Effects)
    UParticleSystem* ImpactVFX;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    USphereComponent* SphereComp;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UParticleSystemComponent* EffectComp;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UProjectileMovementComponent* MovementComp;

	// Called when the game starts or when spawned
	void BeginPlay() override;

	void PostInitializeComponents() override;

protected:
    UFUNCTION()
    virtual void OnHit(UPrimitiveComponent* HitComponent, AActor* Other, UPrimitiveComponent* OtherComponent, FVector Normal, const FHitResult& Hit);

    UFUNCTION()
    virtual void OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void CollideWith(AActor* Other, UPrimitiveComponent* OtherComponent);

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void Explode();
};
