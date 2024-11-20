// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PlayerCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputSubsystems.h"
#include "DataAsset/EnhancedInputData.h"
#include "EnhancedInputComponent.h"
#include "DataAsset/BaseCharacterDataAsset.h"

APlayerCharacter::APlayerCharacter()
{
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->bUsePawnControlRotation = true;
	SpringArmComponent->TargetArmLength = 400.0f;
	SpringArmComponent->AddLocalOffset(FVector(0.0f, 0.0f, 40.0f));


	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent);
	CameraComponent->bUsePawnControlRotation = false;
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	AddMappingContext();

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (EnhancedInputData) {
		EnhancedInputComponent->BindAction(EnhancedInputData->IA_Look, ETriggerEvent::Triggered,this, &APlayerCharacter::Look);
		EnhancedInputComponent->BindAction(EnhancedInputData->IA_Move, ETriggerEvent::Triggered,this, &APlayerCharacter::Move);
	}

}

void APlayerCharacter::AddMappingContext()
{
	APlayerController* PlayerController = Cast<APlayerController>(GetController());

	if (PlayerController == nullptr)
		return;

	UEnhancedInputLocalPlayerSubsystem* Subsystem
		= ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>
		(PlayerController->GetLocalPlayer());

	// Input mapping context
	if (Subsystem == nullptr && EnhancedInputData == nullptr)
		return;

	Subsystem->AddMappingContext(EnhancedInputData->InputMappingContext, 0);
}

void APlayerCharacter::Look(const FInputActionValue& Value)
{
	const FVector2D LookValue = Value.Get<FVector2D>();

	// == 0
	if (LookValue.X != 0.0)
		APawn::AddControllerYawInput(LookValue.X);

	if (LookValue.Y != 0.0)
		APawn::AddControllerPitchInput(LookValue.Y);
}

void APlayerCharacter::Move(const FInputActionValue& Value)
{
	const FVector2D MoveValue = Value.Get<FVector2D>();

	const FRotator MyControllerRotation=  FRotator(0.0, GetControlRotation().Yaw, 0.0);
	// right left
	FVector RightDirection = MyControllerRotation.RotateVector(FVector(0, 1, 0));
	if(MoveValue.X != 0)
		AddMovementInput(RightDirection, MoveValue.X);
    
	FVector FowardDirection = MyControllerRotation.RotateVector(FVector(1, 0, 0));
	if (MoveValue.Y != 0)
		AddMovementInput(FowardDirection, MoveValue.Y);

}

