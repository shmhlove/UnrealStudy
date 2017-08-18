// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Runtime/Core/Public/Delegates/DelegateCombinations.h"
#include "UObject/NoExportTypes.h"
#include "WebConnection.generated.h"

//DECLARE_DELEGATE_OneParam(FTokenCompleteSignature, const FString&);
// 블루프린터에서 이벤트를 연결할 수 있도록 수정
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTokenCompleteSignature, const FString&, Token);

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

public:
	//FTokenCompleteSignature TokenCompleteDelegate;

	// 블루프린터에서 이벤트를 연결할 수 있도록 수정
	UPROPERTY(BlueprintAssignable, Category = "WebService")
	FTokenCompleteSignature TokenCompleteDelegate;
};

DECLARE_LOG_CATEGORY_EXTERN(WebConnection, Log, All);