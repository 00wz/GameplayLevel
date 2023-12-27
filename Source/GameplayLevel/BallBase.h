#pragma once

#include "..\..\Intermediate\ProjectFiles\Delegates.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BallBase.generated.h"

UCLASS()
class GAMEPLAYLEVEL_API ABallBase : public AActor
{
	GENERATED_BODY()
	
public:	
	ABallBase();

	UPROPERTY(VisibleAnyWhere, BlueprintReadonly)
		UStaticMeshComponent* MeshComponent;

	BallBaseDelegate OnDestroyBall;
protected:
	virtual void BeginPlay() override;

	virtual void Destroyed() override;

	UPROPERTY(EditDefaultsOnly)
		FVector MoveSpeed;
public:	
	virtual void Tick(float DeltaTime) override;
	
	void SetMoveSpeed(FVector NewSpeed);
	
	FVector GetMoveSpeed();
	
private:
	void Move(float DeltaTime);
};
