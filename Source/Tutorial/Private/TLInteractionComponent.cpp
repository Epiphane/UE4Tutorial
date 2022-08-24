// Fill out your copyright notice in the Description page of Project Settings.

#include "TLGameplayInterface.h"
#include "TLInteractionComponent.h"
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
UTLInteractionComponent::UTLInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTLInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTLInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTLInteractionComponent::PrimaryInteract()
{
	AActor* Owner = GetOwner();

	FVector EyeLocation;
	FRotator EyeRotation;
	Owner->GetActorEyesViewPoint(EyeLocation, EyeRotation);

	FVector Start = EyeLocation;
	FVector End = EyeLocation + 300 * EyeRotation.Vector();

	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);

    //FHitResult Hit;
    //bool bBlockingHit = GetWorld()->LineTraceSingleByObjectType(Hit, Start, End, ObjectQueryParams);

	float Radius = 50;

	FCollisionShape Shape;
	Shape.SetSphere(Radius);

	TArray<FHitResult> Hits;
	bool bBlockingHit = GetWorld()->SweepMultiByObjectType(Hits, Start, End, FQuat::Identity, ObjectQueryParams, Shape);
	
	FColor LineColor = bBlockingHit ? FColor::Green : FColor::Red;
	for (const FHitResult& Hit : Hits)
	{
        DrawDebugSphere(GetWorld(), Hit.ImpactPoint, Radius, 32, FColor::Blue, false, 2.0f, 0);
        if (AActor* HitActor = Hit.GetActor())
		{
			if (HitActor->Implements<UTLGameplayInterface>())
			{
				APawn* Pawn = Cast<APawn>(Owner);
				ITLGameplayInterface::Execute_Interact(HitActor, Pawn);
				break;
			}
		}
	}

	DrawDebugLine(GetWorld(), Start, End, LineColor, false, 2.0f, 0, 2);
}

