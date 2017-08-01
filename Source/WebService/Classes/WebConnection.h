// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/NoExportTypes.h"
#include "WebConnection.generated.h"

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
	void RequestToken();
};

DECLARE_LOG_CATEGORY_EXTERN(WebConnection, Log, All);