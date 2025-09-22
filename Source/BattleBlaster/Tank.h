// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"

#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputSubsystems.h"

#include "InputAction.h"
#include "InputActionValue.h"
#include "EnhancedInputComponent.h"



#include "Tank.generated.h"

class UCameraComponent;
class UInputMappingContext;

/**
 * 
 */
UCLASS()
class BATTLEBLASTER_API ATank : public ABasePawn
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	ATank();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	UPROPERTY(EditAnywhere, Category = "Input")
	UInputMappingContext* DefaultMappingContext;


	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* RotateAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	float MoveSpeed = 250.f;

	UPROPERTY(EditAnywhere, Category = "Input")
	float RotateSpeed = 250.f;


	

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComponent;


	void MoveInput(const FInputActionValue& Value);
	void RotateInput(const FInputActionValue& Value);
	
};
