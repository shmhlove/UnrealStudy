// Fill out your copyright notice in the Description page of Project Settings.

#include "ABGameInstance.h"
#include "Runtime/Engine/Public/EngineUtils.h"
#include "Runtime/Engine/Classes/Engine/StaticMeshActor.h"
#include "ArenaBattle.h"

UABGameInstance::UABGameInstance()
{
	AB_LOG(Warning, TEXT("%s"), TEXT("Game Instance Constructor Call Start!!"));
	WebConnection = CreateDefaultSubobject<UWebConnection>(TEXT("MyWebConnection"));
	AB_LOG(Warning, TEXT("%s"), TEXT("Game Instance Constructor Call End!!"));
}

void UABGameInstance::RequestTokenComplete(const FString& Token)
{
	AB_LOG(Warning, TEXT("Token : %s"), *Token);
}

void UABGameInstance::Init()
{
	Super::Init();
	AB_LOG_CALLONLY(Warning);
	
	// 모듈간 참조
	auto* ClassInfo1 = WebConnection->GetClass();
	auto* ClassInfo2 = UWebConnection::StaticClass();
	
	if (ClassInfo1 == ClassInfo2)
	{
		AB_LOG(Warning, TEXT("%s"), TEXT("ClassInfo1 is same with ClassInfo2!!"));
	}
	else
	{
		AB_LOG(Warning, TEXT("%s"), TEXT("ClassInfo1 is different with ClassInfo2!!"));
	}

	// 리플렉션
	for (TFieldIterator<UProperty> it(ClassInfo1); it; ++it)
	{
		AB_LOG(Warning, TEXT("Field : %s, Type : %s"), *it->GetName(), *it->GetClass()->GetName());
		UStrProperty* strProp = FindField<UStrProperty>(ClassInfo1, *it->GetName());
		if (NULL != strProp)
		{
			AB_LOG(Warning, TEXT("Value : %s"), *strProp->GetPropertyValue_InContainer(WebConnection));
		}
	}

	for (const auto& entry : ClassInfo1->NativeFunctionLookupTable)
	{
		AB_LOG(Warning, TEXT("Function : %s"), *entry.Name.ToString());
		UFunction* func = ClassInfo1->FindFunctionByName(entry.Name);
		if (0 == func->ParmsSize)
		{
			WebConnection->ProcessEvent(func, NULL);
		}
	}

	// 언리얼 오브젝트의 인스턴스와 기본서브오브젝트의 인스턴스의 관계
	TArray<UObject*> defaultSubobjects;
	GetDefaultSubobjects(defaultSubobjects);
	for (const auto& entry : defaultSubobjects)
	{
		AB_LOG(Warning, TEXT("DefaultSubobject : %s"), *entry->GetClass()->GetName());
		AB_LOG(Warning, TEXT("Outer of DefaultSubobject : %s"), *entry->GetOuter()->GetClass()->GetName());
	}

	if (NULL == WebConnectionNew)
	{
		WebConnectionNew = NewObject<UWebConnection>(this);
	}

	AB_LOG(Warning, TEXT("Outer of NewObject : %s"), *WebConnectionNew->GetOuter()->GetClass()->GetName());

	// 월드 내 액터 검색
	UWorld* currentWorld = GetWorld();
	for (const auto& entry : FActorRange(currentWorld))
	{
		AB_LOG(Warning, TEXT("Actor : %s"), *entry->GetName());

		TArray<UObject*> components;
		entry->GetDefaultSubobjects(components);
		for (const auto& cEntry : components)
		{
			AB_LOG(Warning, TEXT("--- Component : %s"), *cEntry->GetName());
		}
	}

	for (TActorIterator<AStaticMeshActor> it(currentWorld); it; ++it)
	{
		AB_LOG(Warning, TEXT("StaticMesh Actor : %s"), *it->GetName());
	}

	WebConnection->Host = TEXT("localhost");
	WebConnectionNew->Host = TEXT("127.0.0.1");

	// 3가지 객체 : CDO에 있는 객체, 기본서브오브젝트 ( WebConnection )로 있는 객체, 런타임 생성객체 ( WebConnectionNew )
	// ArenaBattle:Warning: UABGameInstance::Init(95) WebConnection Object Host : 
	// ArenaBattle:Warning: UABGameInstance::Init(95) WebConnection Object Host : localhost
	// ArenaBattle:Warning: UABGameInstance::Init(95) WebConnection Object Host : 127.0.0.1
	for (TObjectIterator<UWebConnection> it; it; ++it)
	{
		UWebConnection* conn = *it;
		AB_LOG(Warning, TEXT("WebConnection Object Host : %s"), *conn->Host);
	}

	// 딜리게이트
	//WebConnection->TokenCompleteDelegate.BindUObject(this, &UABGameInstance::RequestTokenComplete);
	WebConnection->TokenCompleteDelegate.AddDynamic(this, &UABGameInstance::RequestTokenComplete);
	WebConnection->RequestToken(TEXT("destiny"));
}