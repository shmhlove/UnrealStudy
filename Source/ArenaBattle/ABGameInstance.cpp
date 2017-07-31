// Fill out your copyright notice in the Description page of Project Settings.

#include "ArenaBattle.h"
#include "ABGameInstance.h"

UABGameInstance::UABGameInstance()
{
	AB_LOG(Warning, TEXT("%s"), TEXT("Game Instance Constructor Call Start!!"));
	WebConnection = CreateDefaultSubobject<UWebConnection>(TEXT("MyWebConnection"));
	AB_LOG(Warning, TEXT("%s"), TEXT("Game Instance Constructor Call End!!"));
}

void UABGameInstance::Init()
{
	Super::Init();
	AB_LOG_CALLONLY(Warning);
}