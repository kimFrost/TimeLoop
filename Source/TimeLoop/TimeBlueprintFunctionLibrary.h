// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "TimeBlueprintFunctionLibrary.generated.h"



UENUM(BlueprintType)
enum EBoolGateEnum
{
	Exits,
	Null
};



UCLASS()
class TIMELOOP_API UTimeBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Util", Meta = (ExpandEnumAsExecs = "Branches"))
	static void NotNull(UObject* Object, TEnumAsByte<EBoolGateEnum>& Branches);
	
};
