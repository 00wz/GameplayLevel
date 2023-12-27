// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BonusBase.h"
#include "BatScalerBonus.generated.h"

UCLASS()
class GAMEPLAYLEVEL_API ABatScalerBonus : public ABonusBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	float WidthRatio;

	virtual void EnableBonus() override;

	virtual void DisableBonus() override;
};
