#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HealthScoreWidget.generated.h"

UCLASS(Abstract, Blueprintable)
class GAMEPLAYLEVEL_API UHealthScoreWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
	void SetHealth(int value);
	
	UFUNCTION(BlueprintImplementableEvent)
	void SetScore(int value);
	
	//UFUNCTION(BlueprintImplementableEvent)
	//void SetRecordScore(int value);
};
