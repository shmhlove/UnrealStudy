// Fill out your copyright notice in the Description page of Project Settings.

#include "ABGameInstance.h"
#include "ArenaBattle.h"

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
}