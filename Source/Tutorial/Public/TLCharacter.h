// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TLCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UTLInteractionComponent;
class UAnimMontage;

UCLASS()
class TUTORIAL_API ATLCharacter : public ACharacter
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, Category = "Attack")
	UAnimMontage* AttackAnim;

    UPROPERTY(EditAnywhere, Category = "Attack")
    TSubclassOf<AActor> MagicProjectileClass;

    UPROPERTY(EditAnywhere, Category = "Attack")
    TSubclassOf<AActor> BlackHoldProjectileClass;

    UPROPERTY(EditAnywhere, Category = "Attack")
    TSubclassOf<AActor> TeleportProjectileClass;

	FTimerHandle TimerHandle_Attack;

public:
	// Sets default values for this character's properties
	ATLCharacter();

protected:

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere)
	UTLInteractionComponent* InteractionComp;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveForward(float value);
	void MoveSideways(float value);
    void PrimaryAttack();
    void SecondaryAttack();
    void TernaryAttack();
	void PrimaryInteract();

    void PrimaryAttack_TimeElapsed();
    void SecondaryAttack_TimeElapsed();
    void TernaryAttack_TimeElapsed();

	void SpawnProjectile(TSubclassOf<AActor> ProjectileClass);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
