// Fill out your copyright notice in the Description page of Project Settings.

#include "TimeLoop.h"
#include "TimeBlueprintFunctionLibrary.h"




/******************** NotNull *************************/
void UTimeBlueprintFunctionLibrary::NotNull(UObject* Object, TEnumAsByte<EBoolGateEnum>& Branches)
{
	if (Object != nullptr)
	{
		Branches = EBoolGateEnum::Exits;
	}
	else
	{
		Branches = EBoolGateEnum::Null;
	}
}
