// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/GameInstance.h"
#include "Runtime/Engine/Classes/Engine/StreamableManager.h"
#include "Runtime/Core/Public/HAL/FileManager.h"
#include "Runtime/Core/Public/Misc/Parse.h"
#include "Runtime/CoreUObject/Public/Misc/PackageName.h"
#include "Runtime/CoreUObject/Public/UObject/Package.h"
// Build.cs에 public DependencyModuleNames로 인해 경로지정없이 사용할 수 있음.
#include "WebConnection.h"
#include "ABGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class ARENABATTLE_API UABGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UABGameInstance();
	override void Init();

public:
    UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "WebService")
    class UWebConnection* WebConnection;

	UPROPERTY()
	class UWebConnection* WebConnectionNew;

	FStreamableManager AssetLoader;

public:
	UFUNCTION()
	void RequestTokenComplete(const FString& Token);

public:
	friend FArchive& operator<<(FArchive& Ar, UWebConnection& WC)
	{
		if (Ar.IsLoading())
		{
			UE_LOG(LogTemp, Warning, TEXT("Archive is Loading State"));
		}
		else if (Ar.IsSaving())
		{
			UE_LOG(LogTemp, Warning, TEXT("Archive is Saving State"));
		}
		else
		{
			return Ar;
		}

		return Ar << WC.Host << WC.URI;
	}
};
