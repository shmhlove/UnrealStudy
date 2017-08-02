// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Runtime/Core/Public/Delegates/DelegateCombinations.h"
#include "UObject/NoExportTypes.h"
#include "WebConnection.generated.h"

DECLARE_DELEGATE_OneParam(FTokenCompleteSignature, const FString&);

/**
 * 
 */
UCLASS()
class WEBSERVICE_API UWebConnection : public UObject
{
	GENERATED_BODY()

public:
	UWebConnection();

public:
	UPROPERTY()
	FString Host;
	
	UPROPERTY()
	FString URI;

public:
	UFUNCTION()
	void RequestToken(const FString& UserID);
	FTokenCompleteSignature TokenCompleteDelegate;
};

DECLARE_LOG_CATEGORY_EXTERN(WebConnection, Log, All);