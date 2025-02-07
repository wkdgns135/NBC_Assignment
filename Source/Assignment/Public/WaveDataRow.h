// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h" // FTableRowBase 정의가 들어있는 헤더
#include "WaveDataRow.generated.h"

USTRUCT(BlueprintType)
struct FWaveDataRow : public FTableRowBase
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 WaveDuration;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 CoinSpawn;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FIntPoint CoinValueRange;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 PositiveItem;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 NegativeItem;
};