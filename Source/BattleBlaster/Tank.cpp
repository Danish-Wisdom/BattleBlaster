// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"

#include "InputMappingContext.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"

ATank::ATank()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(RootComponent);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent);
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();


	
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer())
		{
			if (UEnhancedInputLocalPlayerSubsystem* EnhancedInputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer))
			{
				EnhancedInputSubsystem->AddMappingContext(DefaultMappingContext, 0);
			}
		}
	}
	
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		FHitResult Hit;
		PlayerController->GetHitResultUnderCursor(ECC_Visibility, false, Hit);

		

		DrawDebugSphere(GetWorld(), Hit.ImpactPoint, 25.0f, 8, FColor::Yellow);
	}
	
}




// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATank::MoveInput);
		EnhancedInputComponent->BindAction(RotateAction, ETriggerEvent::Triggered, this, &ATank::RotateInput);
	}
}

void ATank::MoveInput(const FInputActionValue& Value)
{
	float InputValue = Value.Get<float>();
	//UE_LOG(LogTemp, Display, TEXT("Move Input: %f"), InputValue);


	FVector DeltaLocation(0.f);
	DeltaLocation.X = InputValue * UGameplayStatics::GetWorldDeltaSeconds(GetWorld()) * MoveSpeed;
	
	AddActorLocalOffset(DeltaLocation, true);
}

void ATank::RotateInput(const FInputActionValue& Value)
{
	float InputValue = Value.Get<float>();

	FRotator DeltaRotation(0.f);
	DeltaRotation.Yaw = InputValue * UGameplayStatics::GetWorldDeltaSeconds(GetWorld()) * RotateSpeed;

	AddActorLocalRotation(DeltaRotation, true);
}
