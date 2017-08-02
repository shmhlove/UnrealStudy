// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/GameInstance.h"
#include "Runtime/Engine/Classes/Engine/StreamableManager.h"
// Build.cs�� public DependencyModuleNames�� ���� ����������� ����� �� ����.
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
	virtual void Init() override;

public:
	UPROPERTY()
	class UWebConnection* WebConnection;

	UPROPERTY()
	class UWebConnection* WebConnectionNew;

	FStreamableManager AssetLoader;
};
