// Fill out your copyright notice in the Description page of Project Settings.

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
	// Sets default values for this pawn's properties
	ABatBase();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MoveSpeed;

	UPROPERTY(EditDefaultsOnly);
	TSubclassOf<ABallBase> BallClass;
/*
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		UStaticMeshComponent* BallSpawnPoint;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		AActor* Actor;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		UChildActorComponent* Child;*/
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnyWhere, BlueprintReadonly)
		UStaticMeshComponent* MeshComponent;

	UFUNCTION(BlueprintCallable)
		void ThrowBall();

	UFUNCTION(BlueprintImplementableEvent)
		USceneComponent* GetBallSpawnPoint();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
		ABallBase* SpawnBall();

	UPROPERTY(EditAnyWhere, BlueprintReadonly)
		float BallSpeed;

private:
	void MoveRight(float Value);

	UWorld* World;

	TArray<ABallBase*> ReadyBalls;

	//ABallBase* ReadyBall;

	//bool IsConstructorWorked = false;
	//bool IsBeginPlayWorked = false;
};
