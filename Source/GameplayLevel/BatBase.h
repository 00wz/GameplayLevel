#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BallBase.h"
#include "BatBase.generated.h"

UCLASS(Abstract, Blueprintable)
class GAMEPLAYLEVEL_API ABatBase : public APawn
{
	GENERATED_BODY()

public:
	ABatBase();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MoveSpeed;

	UPROPERTY(EditDefaultsOnly);
	TSubclassOf<ABallBase> BallClass;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnyWhere, BlueprintReadonly)
		UStaticMeshComponent* MeshComponent;

	UFUNCTION(BlueprintCallable)
		void ThrowBall();

	UFUNCTION(BlueprintImplementableEvent)
		USceneComponent* GetBallSpawnPoint();

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
		ABallBase* SpawnBall();

	UPROPERTY(EditAnyWhere, BlueprintReadonly)
		float BallSpeed;

private:
	void MoveRight(float Value);

	UWorld* World;

	TArray<ABallBase*> ReadyBalls;

};
