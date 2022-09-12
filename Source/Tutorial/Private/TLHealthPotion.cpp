// Fill out your copyright notice in the Description page of Project Settings.


#include "TLHealthPotion.h"
#include "TLAttributesComponent.h"
#include "Components/CapsuleComponent.h"

// Sets default values
ATLHealthPotion::ATLHealthPotion()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>("SphereComp");
	RootComponent = CapsuleComp;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	StaticMesh->SetupAttachment(CapsuleComp);
}

void ATLHealthPotion::Reactivate()
{
    SetActorHiddenInGame(false);
	SetActorEnableCollision(true);
}

void ATLHealthPotion::Interact_Implementation(APawn* InstigatorPawn)
{
	if (ensure(InstigatorPawn))
	{
		UTLAttributesComponent* Attributes = Cast<UTLAttributesComponent>(InstigatorPawn->GetComponentByClass(UTLAttributesComponent::StaticClass()));
		if (Attributes)
		{
			if (Attributes->ApplyHealthChange(HealAmount))
			{
				SetActorHiddenInGame(true);
                SetActorEnableCollision(false);

				GetWorldTimerManager().SetTimer(TimerHandle_Reactivate, this, &ATLHealthPotion::Reactivate, 10.0f);
			}
		}
	}
}
