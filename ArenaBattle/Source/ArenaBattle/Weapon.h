// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

UCLASS(BlueprintType, Blueprintable)
class ARENABATTLE_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class USkeletalMeshComponent* Weapon;

public:
	UFUNCTION(BlueprintCallable, Category = "Weapon|Stat")
	float GetDamage() { return baseDamage; }

private:
	UPROPERTY(BlueprintReadWrite, EditInstanceOnly, Category = "Stat", meta = (AllowPrivateAccess = "true"))
	float baseDamage;
};
