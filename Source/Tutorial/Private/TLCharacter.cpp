// Fill out your copyright notice in the Description page of Project Settings.


#include "TLCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "TLInteractionComponent.h"
#include "DrawDebugHelpers.h"

// Sets default values
ATLCharacter::ATLCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp->SetupAttachment(SpringArmComp);

	InteractionComp = CreateDefaultSubobject<UTLInteractionComponent>("InteractionComp");

	GetCharacterMovement()->bOrientRotationToMovement = true;

	bUseControllerRotationYaw = false;
}

// Called when the game starts or when spawned
void ATLCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATLCharacter::MoveForward(float value)
{
	FRotator ControlRot = GetControlRotation();
    ControlRot.Pitch = 0.0f;
    ControlRot.Roll = 0.0f;

	AddMovementInput(ControlRot.Vector(), value);
}

void ATLCharacter::MoveSideways(float value)
{
    FRotator ControlRot = GetControlRotation();
    ControlRot.Pitch = 0.0f;
    ControlRot.Roll = 0.0f;

    AddMovementInput(FRotationMatrix(ControlRot).GetScaledAxis(EAxis::Y), value);
}

void ATLCharacter::PrimaryAttack()
{
	PlayAnimMontage(AttackAnim);

	GetWorldTimerManager().SetTimer(TimerHandle_Attack, this, &ATLCharacter::PrimaryAttack_TimeElapsed, 0.2f);
}

void ATLCharacter::SecondaryAttack()
{
    PlayAnimMontage(AttackAnim);

    GetWorldTimerManager().SetTimer(TimerHandle_Attack, this, &ATLCharacter::SecondaryAttack_TimeElapsed, 0.2f);
}

void ATLCharacter::TernaryAttack()
{
    PlayAnimMontage(AttackAnim);

    GetWorldTimerManager().SetTimer(TimerHandle_Attack, this, &ATLCharacter::TernaryAttack_TimeElapsed, 0.2f);
}

void ATLCharacter::PrimaryAttack_TimeElapsed()
{
	SpawnProjectile(MagicProjectileClass);
}

void ATLCharacter::SecondaryAttack_TimeElapsed()
{
    SpawnProjectile(TeleportProjectileClass);
}

void ATLCharacter::TernaryAttack_TimeElapsed()
{
    SpawnProjectile(BlackHoldProjectileClass);
}

void ATLCharacter::SpawnProjectile(TSubclassOf<AActor> ProjectileClass)
{
    if (ensureAlways(ProjectileClass))
    {
        FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");

        FVector TraceStart = CameraComp->GetComponentLocation();
        FVector TraceEnd = TraceStart + 5000 * GetControlRotation().Vector();

        FCollisionObjectQueryParams ObjectQueryParams;
        ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);
        ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldStatic);
        ObjectQueryParams.AddObjectTypesToQuery(ECC_Pawn);

        FHitResult Hit;
        if (GetWorld()->LineTraceSingleByObjectType(Hit, TraceStart, TraceEnd, ObjectQueryParams))
        {
            TraceEnd = Hit.ImpactPoint;
        }

        FVector Direction = TraceEnd - HandLocation;
        FRotator ProjectileRotation = Direction.Rotation();

        FTransform SpawnTM = FTransform(ProjectileRotation, HandLocation);

        FActorSpawnParameters SpawnParams;
        SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
        SpawnParams.Instigator = this;

        GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTM, SpawnParams);
    }
}

void ATLCharacter::PrimaryInteract()
{
	if (InteractionComp)
	{
		InteractionComp->PrimaryInteract();
	}
}

// Called every frame
void ATLCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ATLCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ATLCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveSideways", this, &ATLCharacter::MoveSideways);
    PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

    PlayerInputComponent->BindAction("PrimaryAttack", IE_Pressed, this, &ATLCharacter::PrimaryAttack);
    PlayerInputComponent->BindAction("SecondaryAttack", IE_Pressed, this, &ATLCharacter::SecondaryAttack);
    PlayerInputComponent->BindAction("TernaryAttack", IE_Pressed, this, &ATLCharacter::TernaryAttack);
    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("PrimaryInteract", IE_Pressed, this, &ATLCharacter::PrimaryInteract);
}

