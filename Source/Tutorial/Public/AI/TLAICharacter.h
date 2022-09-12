// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TLAttributesComponent.h"
#include "TLAICharacter.generated.h"

UCLASS()
class TUTORIAL_API ATLAICharacter : public ACharacter
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere)
	UTLAttributesComponent* AttributesComp;

public:
	// Sets default values for this character's properties
	ATLAICharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
