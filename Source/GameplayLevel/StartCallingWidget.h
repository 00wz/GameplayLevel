#pragma once

#include "..\..\Intermediate\ProjectFiles\Delegates.h"
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StartCallingWidget.generated.h"


UCLASS()
class GAMEPLAYLEVEL_API UStartCallingWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	NoParamDelegate OnPressStart;
private:
	UFUNCTION(BlueprintCallable)
		void StartGame();
};
