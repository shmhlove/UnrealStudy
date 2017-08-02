// Fill out your copyright notice in the Description page of Project Settings.

//#include "../Pubilc/WebService.h"
#include "WebConnection.h"

DEFINE_LOG_CATEGORY(WebConnection);

UWebConnection::UWebConnection()
{
	UE_LOG(WebConnection, Warning, TEXT("WebConnection Constructor Call!!"));
}

void UWebConnection::RequestToken(const FString& UserID)
{
	UE_LOG(WebConnection, Warning, TEXT("WebConnection RequestToken Call!!"));
	//TokenCompleteDelegate.ExecuteIfBound(TEXT("0LCJydGkiOiI2a3NjVE9pTUNESVZWM05qVTIyUnlTIn0.VJyMOicM"));

	// 블루프린터에서 이벤트를 연결할 수 있도록 수정
	TokenCompleteDelegate.Broadcast(TEXT("0LCJydGkiOiI2a3NjVE9pTUNESVZWM05qVTIyUnlTIn0.VJyMOicM"));
}