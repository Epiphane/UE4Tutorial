// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TLProjectile.h"
#include "TLMagicProjectile.generated.h"

class UCameraShakeBase;

UCLASS()
class TUTORIAL_API ATLMagicProjectile : public ATLProjectile
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	float Damage = 20.0f;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UCameraShakeBase> Shake;

protected:
	UPROPERTY(VisibleAnywhere)
	UAudioComponent* AudioComp;

	UPROPERTY(EditDefaultsOnly)
	USoundBase* ImpactSound;

protected:
	void CollideWith_Implementation(AActor* Other, UPrimitiveComponent* OtherComponent) override;

	void Explode_Implementation() override;

protected:
	ATLMagicProjectile();
};
