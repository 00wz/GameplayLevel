// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BonusBase.h"
#include "Engine/DataAsset.h"
#include "BonusesConfig.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPLAYLEVEL_API UBonusesConfig : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
		TArray<TSubclassOf<ABonusBase> > BonusClasses;

	UPROPERTY(EditAnywhere)
		float BonusFallSpeed;
};
