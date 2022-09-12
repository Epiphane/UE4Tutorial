// Fill out your copyright notice in the Description page of Project Settings.


#include "TLAttributesComponent.h"
#include <algorithm>

// Sets default values for this component's properties
UTLAttributesComponent::UTLAttributesComponent()
{
	Health = 100;
	HealthMax = 100;
}

bool UTLAttributesComponent::IsAlive() const
{
	return Health > 0;
}

bool UTLAttributesComponent::ApplyHealthChange(float Delta)
{
	float NewHealth = FMath::Clamp(Health + Delta, 0.f, HealthMax);
	if (NewHealth == Health)
	{
		return false;
	}

	Health = NewHealth;
	OnHealthChanged.Broadcast(nullptr, this, Health, Delta);
	return true;
}
