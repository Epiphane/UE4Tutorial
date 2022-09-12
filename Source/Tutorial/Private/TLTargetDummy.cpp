// Fill out your copyright notice in the Description page of Project Settings.


#include "TLTargetDummy.h"

#include "Components/StaticMeshComponent.h"
#include "TLAttributesComponent.h"

// Sets default values
ATLTargetDummy::ATLTargetDummy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	RootComponent = MeshComp;

	AttributesComp = CreateDefaultSubobject<UTLAttributesComponent>("AttributesComp");
	AttributesComp->OnHealthChanged.AddDynamic(this, &ATLTargetDummy::OnHealthChanged);
}

void ATLTargetDummy::OnHealthChanged(AActor* InstigatorActor, UTLAttributesComponent* OwningComp, float NewHealth, float Delta)
{
	if (Delta < 0)
	{
		MeshComp->SetScalarParameterValueOnMaterials("TimeToHit", GetWorld()->TimeSeconds);
	}
}

