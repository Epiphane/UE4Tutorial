// Fill out your copyright notice in the Description page of Project Settings.


#include "TLExplosiveBarrel.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "DrawDebugHelpers.h"

// Sets default values
ATLExplosiveBarrel::ATLExplosiveBarrel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	StaticMesh->SetCollisionProfileName("PhysicsActor");
	StaticMesh->SetSimulatePhysics(true);
	RootComponent = StaticMesh;

	RadialForce = CreateDefaultSubobject<URadialForceComponent>("RadialForce");
	RadialForce->SetupAttachment(StaticMesh);
	RadialForce->bImpulseVelChange = true;
	RadialForce->ImpulseStrength = 2000;
    RadialForce->Radius = 750;
	RadialForce->SetAutoActivate(false);
	RadialForce->AddCollisionChannelToAffect(ECC_WorldDynamic);
}

// Called when the game starts or when spawned
void ATLExplosiveBarrel::BeginPlay()
{
	Super::BeginPlay();
}

void ATLExplosiveBarrel::PostInitializeComponents()
{
	Super::PostInitializeComponents();

    StaticMesh->OnComponentHit.AddDynamic(this, &ATLExplosiveBarrel::OnHit);
}

// Called every frame
void ATLExplosiveBarrel::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ATLExplosiveBarrel::OnHit(UPrimitiveComponent* HitComponent, AActor* Other, UPrimitiveComponent* OtherComponent, FVector Normal, const FHitResult& Hit)
{
	RadialForce->FireImpulse();

	UE_LOG(LogTemp, Log, TEXT("ATLExplosiveBarrel::OnHit"));
	UE_LOG(LogTemp, Warning, TEXT("Other actor: %s at game time %f"), *GetNameSafe(Other), GetWorld()->TimeSeconds);

	FString CombinedString = FString::Printf(TEXT("Hit at location: %s"), *Hit.ImpactPoint.ToString());
	DrawDebugString(GetWorld(), Hit.ImpactPoint, CombinedString, nullptr, FColor::Green, 2.0f, true);
}

