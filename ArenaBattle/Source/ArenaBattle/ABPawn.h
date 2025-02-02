// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "limits.h"
#include "CoreMinimal.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Runtime/Engine/Classes/Components/CapsuleComponent.h"
#include "Runtime/Engine/Classes/Components/ArrowComponent.h"
#include "Runtime/Engine/Classes/GameFramework/SpringArmComponent.h"
#include "Runtime/Engine/Classes/GameFramework/FloatingPawnMovement.h"
#include "Runtime/Engine/Classes/Camera/CameraComponent.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/Pawn.h"
#include "ABPawn.generated.h"

UCLASS(config=Game)
class ARENABATTLE_API AABPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AABPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Collision")
    class UCapsuleComponent* Body;
 
    UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Visual")
    class USkeletalMeshComponent* Mesh;
 
    UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Helper")
    class UArrowComponent* Arrow;
 
    UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Camera")
    class USpringArmComponent* SpringArm;
 
    UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Camera")
    class UCameraComponent* Camera;
 
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Movement")
	class UFloatingPawnMovement* Movement;

    UPROPERTY(config, BlueprintReadWrite, EditDefaultsOnly, Category = "Stat")
    float MaxHP;
 
    UPROPERTY(BlueprintReadWrite, EditInstanceOnly, Category = "Stat")
    float CurrentHP;

	UFUNCTION()
	void CharacterMeshDeferred();
	//FStreamableDelegate StreamableDelegate;

private:
	int32 NewIndex;

	UPROPERTY(config)
	TArray<FStringAssetReference> CharacterAssets;

	float CurrentLeftRightVal;
	float CurrentUpDownVal;

	UFUNCTION()
	void UpDownInput(float NewInputVal);

	UFUNCTION()
	void LeftRightInput(float NewInputVal);
};
