// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/BaseCharacter.h"
#include "PlayerCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UEnhancedInputData;
struct FInputActionValue;

/**
 * 
 */
UCLASS()
class BASE_WAR_API APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()
public:
	APlayerCharacter();
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void AddMappingContext();
private:
	void Look(const FInputActionValue& Value);
	void Move(const FInputActionValue& Value);

private:
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(EditDefaultsOnly, Category = "DataAsset_EnhancedInput")
	UEnhancedInputData* EnhancedInputData;
};
